//
// Created by kfrai on 2025-02-13.
//

#ifndef TOWER_H
#define TOWER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "Cell.h"
#include "TowerObserver.h"
#include <memory>


struct Cell;
class Player;
class Map;
class Critter;
class TargetingStrategy;

class Tower {
private:
    int level;
    std::string name;
    int maxLevel;
    float price;
    float upgradeRate;
    float refundRate;
    float refundAmt;
    int range;
    float damage;
    float rateOfFire;
    std::string strat;

    std::unique_ptr<TargetingStrategy> targetingStrategy;

    bool active = false;
    Player *player;

    struct Position {
        int x, y;

        // Constructor that takes two arguments
        Position(int xVal, int yVal) : x(xVal), y(yVal) {}
    } position;

    static Map *map;

    std::vector<TowerObserver*> observers;

protected:
    int rOfCounter;
    std::vector<Cell *> cells;
    float damageUpgrade;
    float RoFUpgrade;
    int rangeUpgrade;

public:
    // constructors and destructor
    Tower();

    Tower(int x, int y, Player *player, std::string name, int level, int maxLevel, float basePrice, float upgradeRate,
          float refundRate, int range, float damage, float rateOfFire);

    Tower(int x, int y, Player *player, std::string name, int maxLevel, float basePrice, int range, float damage,
          float rateOfFire);

    Tower(Tower *tower);

    ~Tower();

    // getters
    Player *getPlayer();

    std::string getName();

    int getLevel() const;

    int getPositionX() const;

    int getPositionY() const;

    int getMaxLevel() const;

    float getPrice() const;

    float getUpgradeRate() const;

    float getRefundAmt() const;

    float getRefundRate() const;

    int getRange() const;

    float getDamage() const;

    float getRateOfFire() const;

    float getDamageUpgrade() const;

    float getRoFUpgrade() const;

    int getRangeUpgrade() const;

    float getUpgradePrice();

    std::string getStrat() const;

    static void setMap(Map *map);

    // setters

    void setTargetingStrategy(std::unique_ptr<TargetingStrategy> strategy);

    void setPlayer(Player *player);

    void setName(std::string name);

    void setLevel(int level);

    void setMaxLevel(int maxLevel);

    void setPrice(float price);

    void setUpgradeRate(float upgradeRate);

    void setRefundAmt(float refundAmt);

    void setRefundRate(float refundRate);

    void setRange(int range);

    void setDamage(float damage);

    void setRateOfFire(float rateOfFire);

    static Map *getMap();

    // tower methods
    bool purchase();

    void upgrade(int range, float damage, float rateOfFire);

    virtual void upgrade();

    void setInitialPosition();

    virtual CellType getTowerType() const;

    void applyEffect(Critter *critter);

    void enterCoords();

    void createRange();

    void addCellToRange(int tileAddX, int tileAddY);

    virtual void checkRange();

    virtual void critterProtocol(Critter* critter);

    void attack(int x, int y);

    // debugging
    void printInfo();

    // Observer methods
    void addObserver(TowerObserver* observer);
    void removeObserver(TowerObserver* observer);
    void notifyObservers(const std::string& message) const;
};


#endif //TOWER_H
