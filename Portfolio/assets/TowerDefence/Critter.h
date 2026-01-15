#ifndef CRITTER_H
#define CRITTER_H

#include <string>
#include <vector>
#include "Map.h"
#include <set>

class Player;
class Observer;

class Critter : public Subject {
protected:
    std::string name;
    int level;
    int hitPoints;
    int speed;
    int strength;
    int reward;
    int positionX;
    int positionY;
    Map* map;
    sf::CircleShape shape;

    std::set<std::pair<int, int>> visitedCells;  // Set to track visited cells


    std::vector<Observer*> observers;
    static Player* player;

    int burningDuration = 0;
    int burningDamagePerTick = 0;

public:
    Critter(std::string name, int level, Map* m, int startX, int startY);

    // Getters
    std::string getName() const;
    int getHitPoints() const;
    int getSpeed() const;
    int getStrength() const;
    int getReward() const;
    int getX() const;
    int getY() const;
    sf::CircleShape* getShape();

    // Observer Methods
    void Attach(Observer *obs) override;
    void Detach(Observer *obs) override;
    void Notify() override;

    // Behavior methods
    void takeDamage(int damage);
    bool isDead() const;
    void move();
    void display() const;
    Map* getMap() const;

    static void setPlayer(Player *player);

    void setBurning(int duration, int damagePerTick);
    void updateStatus();
    void reduceSpeed(float factor);

    int getDistanceToExit() const;

    int getDistanceToTower(int towerX, int towerY) const;
};


#endif // CRITTER_H
