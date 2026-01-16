//
// Created by kfrai on 2025-02-15.
//

#ifndef SNIPER_TOWER_H
#define SNIPER_TOWER_H
#include "Tower.h"

class SniperTower : public Tower {
private:

public:
    static std::string sName;
    static int sMaxLevel;
    static float sPrice;
    static int sRange;
    static float sDamage;
    static float sRoF;

    SniperTower(Player *player, int x, int y);

    void upgrade();

    void critterProtocol(Critter *critter) override;

    CellType getTowerType() const override;
};

#endif //SNIPER_TOWER_H
