#include "Critter.h"
#include <cmath> // For scaling calculations
#include <iostream>
#include <vector>
#include <set>

#include "CritterStats.h"
#include "Player.h"

// Static member variable to store the player
Player* Critter::player = nullptr;

// Constructor for the Critter class, initializes its attributes based on level and position
Critter::Critter(std::string name, int level, Map* m, int startX, int startY)
    : name(name), level(level), map(m), positionX(startX), positionY(startY) {
    // Scale attributes based on the critter's level
    hitPoints = (50 + (level * 10)); // HP increases with level
    speed = 1 + (level / 2);         // Speed increases with level (level / 2 for scaling)
    strength = level;                // Strength equals level
    reward = (level * 3);            // Reward for the player if this critter is defeated

    // Set the critter's initial position on the map
    map->setCell(positionX, positionY, CRITTER);

    // Register the new critter with the CritterStats for tracking
    CritterStats::addNewCritter(this);

    // Setup the shape of the critter (for visualization or GUI rendering)
    shape.setRadius(21);
    shape.setPointCount(4);   // A 4-point shape (a square)
    shape.setFillColor(sf::Color(0x621313ff)); // Set the fill color (red)
    shape.setOutlineColor(sf::Color::White);  // Set the outline color (white)
    shape.setOutlineThickness(3);            // Set the thickness of the outline
    shape.setOrigin(shape.getGeometricCenter()); // Set the shape's origin to its center

    // Initialize the visitedCells set to track the positions the critter has already visited
    visitedCells.insert({positionX, positionY});
}

// Observer pattern methods to allow observers to listen to changes in the critter
void Critter::Attach(Observer* obs) {
    observers.push_back(obs); // Add an observer to the list
}

void Critter::Detach(Observer* obs) {
    // Remove an observer from the list
    observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
}

void Critter::Notify() {
    // Notify all attached observers about the change
    for (Observer* obs : observers) {
        obs->Update(this); // Call the update method on each observer
    }
}

// Getters for the critter's attributes
std::string Critter::getName() const { return name; }
int Critter::getHitPoints() const { return hitPoints; }
Map * Critter::getMap() const { return map; }
int Critter::getSpeed() const { return speed; }
int Critter::getStrength() const { return strength; }
int Critter::getReward() const { return reward; }
int Critter::getX() const { return positionX; }
int Critter::getY() const { return positionY; }

sf::CircleShape* Critter::getShape() {
    return &shape; // Return the shape of the critter for rendering
}

// Method to handle the critter taking damage
void Critter::takeDamage(int damage) {
    hitPoints -= damage; // Reduce hit points by the damage amount
    std::cout << name << " took " << damage << " damage. HP left: " << hitPoints << std::endl;

    // Ensure hit points do not go below zero
    if (hitPoints < 0) hitPoints = 0;

    // Notify observers of the change
    Notify();
}

// Method to check if the critter is dead
bool Critter::isDead() const {
    if (hitPoints <= 0) {
        // If the critter is dead, mark its position on the map as PATH
        map->setCell(positionX, positionY, PATH);
        std::cout << name << " died." << std::endl;

        // Remove the critter from the cell
        Cell* oldCell = &(map->getCell(positionX, positionY));
        if (oldCell) {
            oldCell->removeCritter();
        }

        // Remove the critter from the global stats
        CritterStats::removeCritter(this);
        return true;
    }
    return false;
}

// Method to reduce the critter's speed by a factor
void Critter::reduceSpeed(float factor) {
    speed = static_cast<int>(speed * factor); // Adjust speed by multiplying with the factor
}

// Update method to handle status effects like burning
void Critter::updateStatus() {
    if (burningDuration > 0) {
        // If the critter is burning, apply damage and reduce burn duration
        takeDamage(burningDamagePerTick);
        burningDuration--;

        if (burningDuration <= 0) {
            std::cout << name << " has stopped burning.\n";
        }
    }
}

// Method to set the critter on fire
void Critter::setBurning(int duration, int damagePerTick) {
    burningDuration = duration;
    burningDamagePerTick = damagePerTick;
    std::cout << name << " is now burning for " << duration
              << " ticks at " << damagePerTick << " damage each.\n";
}

// Move the critter on the map, following S-pattern movement and avoiding revisiting cells
void Critter::move() {
    for (int i = 0; i < speed; i++) {
        // Clear the critter's old position on the map
        map->setCell(positionX, positionY, PATH);
        Cell* oldCell = &(map->getCell(positionX, positionY));
        if (oldCell) {
            oldCell->removeCritter();
        }

        // Try to move in an S-pattern (left, right, up, down)
        bool moved = false;
        std::vector<std::pair<int, int>> directions = {
            { -1, 0 }, // Left
            { 1, 0 },  // Right
            { 0, -1 }, // Up
            { 0, 1 }   // Down
        };

        // Loop through directions to find a valid move
        for (auto dir : directions) {
            int newX = positionX + dir.first;
            int newY = positionY + dir.second;

            // Check if the new position is valid and not visited before
            if (map->getCellType(newX, newY) == PATH || map->getCellType(newX, newY) == EXIT) {
                if (visitedCells.find({newX, newY}) == visitedCells.end()) {
                    // Move to the new valid position
                    positionX = newX;
                    positionY = newY;
                    moved = true;
                    visitedCells.insert({positionX, positionY}); // Mark new position as visited
                    break;
                }
            }
        }

        // If no valid move was found, critter stays at the current position
        if (!moved) {
            std::cout << name << " cannot move. All adjacent cells are blocked.\n";
        }

        // Update the critter's new position on the map
        Cell* newCell = &(map->getCell(positionX, positionY));
        if (newCell && newCell->getCritter() == nullptr) {
            newCell->setCritter(this); // Set the critter in the new cell
        }

        // Mark the new position on the map
        map->setCell(positionX, positionY, CRITTER);
        std::cout << name << " is moving to position (" << positionX << ", " << positionY << ")." << std::endl;

        // Check if the critter has reached the exit
        if (positionX == map->getExitX() && positionY == map->getExitY()) {
            player->loseLife(strength);  // Lose lives equal to critter strength

            std::cout << name << " reached the exit and deducted " << strength << " life/lives!" << std::endl;
            map->setCell(positionX, positionY, EXIT);

            if (newCell) {
                newCell->removeCritter();
            }
        }


        // Notify observers about the move
        Notify();
    }
}

// Display the critter's information (name, stats, position)
void Critter::display() const {
    std::cout << "Critter: " << name << "\nLevel: " << level
              << "\nHP: " << hitPoints
              << "\nSpeed: " << speed
              << "\nStrength: " << strength
              << "\nReward: " << reward
              << "\nPosition: (" << positionX << ", " << positionY << ")\n" << std::endl;
}

// Set the player associated with the critter (for losing coins when critter reaches the exit)
void Critter::setPlayer(Player *newPlayer) {
    player = newPlayer; // Assign the player reference
}

// Get the distance from the critter to the exit
int Critter::getDistanceToExit() const {
    return std::abs(positionX - map->getExitX()) + std::abs(positionY - map->getExitY());
}

// Get the distance from the critter to a tower (used for calculating range or proximity)
int Critter::getDistanceToTower(int towerX, int towerY) const {
    return std::abs(positionX - towerX) + std::abs(positionY - towerY);
}
