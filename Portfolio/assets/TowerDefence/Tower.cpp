//
// Created by kfrai on 2025-02-13.
//

#include "Tower.h"

#include <utility>

#include "Critter.h"
#include "Player.h"
#include "Map.h"
#include "TargetingStrategy.h"
#include "TowerStats.h"
#include "SplashDamageDecorator.h"
#include "BurningDamageDecorator.h"
#include "FreezingDamageDecorator.h"


Map *Tower::map = nullptr;

// Strategy methods

void Tower::setTargetingStrategy(std::unique_ptr<TargetingStrategy> strategy) {
    targetingStrategy = std::move(strategy);
    std::cout << "Targeting strategy set to: " << targetingStrategy->getName() << std::endl;
    strat = targetingStrategy->getName();
}


// Observer methods
void Tower::addObserver(TowerObserver* observer) {
    if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
        observers.push_back(observer);
    }
}

void Tower::removeObserver(TowerObserver* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Tower::notifyObservers(const std::string& message) const {
    for (TowerObserver* observer : observers) {
        if (observer) {
            observer->onTowerUpdate(message);
        }
    }
}

// Constructors
Tower::Tower()
    : position(0,0), player(nullptr), name("Tower"), level(0), maxLevel(4), price(100), upgradeRate(1.5), refundRate(0.4),
      refundAmt(price * refundRate), range(3), damage(50), rateOfFire(1), rOfCounter(0), damageUpgrade(20), RoFUpgrade(1), rangeUpgrade(1), strat("") {
}

Tower::Tower(int x, int y, Player *player, std::string name, int maxLevel, float price, int range, float damage,
             float rateOfFire)
    : position(x, y), player(player), name(std::move(name)), level(0), maxLevel(maxLevel), price(price), upgradeRate(1.5),
      refundRate(0.4),
      refundAmt(price * refundRate), range(range), damage(damage), rateOfFire(rateOfFire), rOfCounter(0), damageUpgrade(20), RoFUpgrade(1), rangeUpgrade(1), strat("")  {
}

Tower::Tower(Tower *tower) : position(tower->position), player(tower->player), name(tower->name), level(tower->level), maxLevel(tower->maxLevel), price(tower->price),
      upgradeRate(tower->upgradeRate),
      refundRate(tower->refundRate), refundAmt(tower->refundRate), range(tower->range), damage(tower->damage), rateOfFire(tower->rateOfFire), rOfCounter(tower->rOfCounter), damageUpgrade(tower->damageUpgrade), RoFUpgrade(tower->RoFUpgrade), rangeUpgrade(tower->rangeUpgrade), strat(tower->strat) {
}

Tower::Tower(int x, int y, Player *player, std::string name, int level, int maxLevel, float basePrice,
             float upgradeRate, float refundRate, int range, float damage, float rateOfFire)
    : position(x, y), player(player), name(std::move(name)), level(level), maxLevel(maxLevel), price(basePrice),
      upgradeRate(upgradeRate),
      refundRate(refundRate), refundAmt(price * refundRate), range(range), damage(damage), rateOfFire(rateOfFire), rOfCounter(0), damageUpgrade(20), RoFUpgrade(1), rangeUpgrade(1), strat("")  {
}


// Destructor, removes range from cells and clears the cell array
Tower::~Tower() {
    for (Cell *cell: cells) {
        cell->setInRangeOfTower(false);
    }
    cells.clear();
    map->setCell(position.x, position.y, SCENERY);
    observers.clear();
}


// Getters
Player *Tower::getPlayer() {
    return player;
}

std::string Tower::getName() {
    return name;
}

int Tower::getLevel() const {
    return level;
}

int Tower::getPositionX() const {
    return position.x;
}

int Tower::getPositionY() const {
    return position.y;
}

int Tower::getMaxLevel() const {
    return maxLevel;
}

float Tower::getPrice() const {
    return price;
}

float Tower::getUpgradeRate() const {
    return upgradeRate;
}

float Tower::getRefundAmt() const {
    return refundAmt;
}

float Tower::getRefundRate() const {
    return refundRate;
}

int Tower::getRange() const {
    return range;
}

float Tower::getDamage() const {
    return damage;
}

float Tower::getRateOfFire() const {
    return rateOfFire;
}

float Tower::getDamageUpgrade() const {
    if (level == maxLevel) return 0;
    return damage + damageUpgrade;
}

float Tower::getRoFUpgrade() const {
    if (level == maxLevel) return 0;
    return rateOfFire - RoFUpgrade;
}

int Tower::getRangeUpgrade() const {
    if (level == maxLevel) return 0;
    return range + rangeUpgrade;
}

float Tower::getUpgradePrice() {
    return price * upgradeRate;
}

std::string Tower::getStrat() const {
    return strat;
}

Map *Tower::getMap() {
    return map;
}

// Setters
void Tower::setLevel(int level) {
    this->level = level;
}

void Tower::setMaxLevel(int maxLevel) {
    this->maxLevel = maxLevel;
}

void Tower::setPrice(float price) {
    this->price = price;
}

void Tower::setUpgradeRate(float upgradeRate) {
    this->upgradeRate = upgradeRate;
}

void Tower::setRefundAmt(float refundAmt) {
    this->refundAmt = refundAmt;
}

void Tower::setRefundRate(float refundRate) {
    this->refundRate = refundRate;
}

void Tower::setRange(int range) {
    this->range = range;
}

void Tower::setDamage(float damage) {
    this->damage = damage;
}

void Tower::setRateOfFire(float rateOfFire) {
    this->rateOfFire = rateOfFire;
}

void Tower::setPlayer(Player *player) {
    this->player = player;
}

void Tower::setName(std::string name) {
    this->name = std::move(name);
}

void Tower::setMap(Map *newMap) {
    map = newMap;
}

// Tower Methods

// Purchase returns false if the tower is already purchased or if the player doesn't have enough funds
bool Tower::purchase() {
    if (level < 1) {
        if (player) {
            active = true;
            refundAmt = price * refundRate;
            price = upgradeRate * price;
            level++;
            setInitialPosition();
            createRange();
            notifyObservers(name + " purchased at (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");
            map->displayMapWithRange();
            TowerStats::addNewTower(this);
            return true;
        } else return false;
    } else {
        std::cout << "You have already purchased this tower!\n" << std::endl;
        return false;
    }
}

// Upgrade takes three upgrade values, updates variables and recreates the range for the tower
void Tower::upgrade() {
    if (level < maxLevel) {
        if (player && player->checkBalance(price)) {
            level++;
            refundAmt = price * refundRate;
            price = upgradeRate * price;
            range = range + rangeUpgrade;
            damage = damage + damageUpgrade;
            if (rateOfFire >= RoFUpgrade) rateOfFire = rateOfFire -= RoFUpgrade;
            cells.clear();
            createRange();
            notifyObservers(name + " upgraded to Level " + std::to_string(level) + "!");
        }
    } else {
        std::cout << "Tower is already max level!\n";
        damageUpgrade = 0;
        rangeUpgrade = 0;
        RoFUpgrade = 0;
    }

    if (level == maxLevel) {
        upgradeRate = 0;
    }
}

// Sets the position of the tower, ensuring the position is within bounds, and it is a valid tile to do so on
void Tower::setInitialPosition() {
    if (map) {
        if (position.x < map->getWidth() && position.y < map->getLength() && map->getCellType(position.x, position.y) ==
            SCENERY) {
            map->setCell(position.x, position.y, getTowerType());
            map->setCellTower(position.x, position.y, this);
        } else {
            enterCoords(); // if the tile is invalid, send to enter new coordinates
        }
    }
}

// Gets tower type for each child tower, used in setInitialPosition to mark the cells correctly
CellType Tower::getTowerType() const {
    return TOWER;
}

void Tower::applyEffect(Critter* critter)
{
    if (!critter) return;
    // Default/base tower simply does direct damage
    critter->takeDamage(getDamage());
    std::cout << "Tower hit a critter for "
              << getDamage() << " damage!\n";
}

// Recursive function with setInitialPosition to make sure the user doesn't continue without valid coordinates
void Tower::enterCoords() {
    std::cout << "Invalid tower placement\nEnter new x position: ";
    std::cin >> position.x;
    std::cout << "Enter new y position: ";
    std::cin >> position.y;
    setInitialPosition();
}

// Algorithm for creating a "circular" range surrounding the tower's position, based on it's range variable
void Tower::createRange() {
    // Checking if the map was created yet
    if (map) {
        int tileAddX, tileAddY;
        int x = position.x;
        int y = position.y;
        // Creating the range extending horizontally and vertically from the tower
        for (int i = 1; i <= range; i++) {
            tileAddX = x + i;
            tileAddY = y;
            addCellToRange(tileAddX, tileAddY);
            tileAddX = x;
            tileAddY = y + i;
            addCellToRange(tileAddX, tileAddY);
            tileAddX = x - i;
            tileAddY = y;
            addCellToRange(tileAddX, tileAddY);
            tileAddX = x;
            tileAddY = y - i;
            addCellToRange(tileAddX, tileAddY);
        }
        // Filling in the rest of the range
        for (int i = 1; i < range; i++) {
            for (int j = (range - i); j >= 1; j--) {
                tileAddX = x + i;
                tileAddY = y + j;
                addCellToRange(tileAddX, tileAddY);
                tileAddX = x + i;
                tileAddY = y - j;
                addCellToRange(tileAddX, tileAddY);
                tileAddX = x - i;
                tileAddY = y + j;
                addCellToRange(tileAddX, tileAddY);
                tileAddX = x - i;
                tileAddY = y - j;
                addCellToRange(tileAddX, tileAddY);
            }
        }
    } else std::cout << "No map exists yet!\n";
}

// Adds cell to cell array and sets the boolean within the cell itself to be true
void Tower::addCellToRange(int tileAddX, int tileAddY) {
    if (tileAddX >= 0 && tileAddX < map->getWidth() && tileAddY >= 0 && tileAddY < map->getLength()) {
        map->getCell(tileAddX, tileAddY).setInRangeOfTower(true);
        cells.push_back(&(map->getCell(tileAddX, tileAddY)));
    }
}

void Tower::checkRange() {
    if (rOfCounter == 0) {
        std::vector<Critter*> crittersInRange;
        for (Cell* cell: cells) {
            if (cell && cell->isOccupiedByCritter()) {
                Critter* critter = cell->getCritter();
                crittersInRange.push_back(critter);
            }
        }
        if (!crittersInRange.empty() && targetingStrategy) {
            Critter* target = targetingStrategy->selectTarget(crittersInRange, this);
            if (target) {
                critterProtocol(target);
            }
        }
        return;
    }
    rOfCounter--;
}

void Tower::critterProtocol(Critter* critter)
{
    // Instead of taking damage directly, call applyEffect!
    applyEffect(critter);
    // Also handle rateOfFire cooldown, if needed:
    rOfCounter = rateOfFire;
}

void Tower::printInfo() {
    std::cout << "--- " << name << "'s Stats: ---\n"
            << "Location : (" << position.x << ", " << position.y << ")\n"
            << "Level : " << level << "\n"
            << "Max Level : " << maxLevel << "\n"
            << "Upgrade Price : " << upgradeRate * price << "$\n"
            << "Refund Amount : " << refundAmt << "$\n"
            << "Damage : " << damage << "\n"
            << "Range : " << range << "\n"
            << "Rate Of Fire : " << rateOfFire << "\n"
            << "-----------------------------\n\n";
}
