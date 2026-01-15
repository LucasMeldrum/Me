//
// Created by kfrai on 2025-02-14.
//

#ifndef BOMBERTOWER_H
#define BOMBERTOWER_H

#include "Tower.h"

class BomberTower : public Tower {
private:


public:
    static std::string bName;
    static int bMaxLevel;
    static float bPrice;
    static int bRange;
    static float bDamage;
    static float bRoF;

    BomberTower(Player *player, int x, int y);

    void critterProtocol(Critter *critter) override;

    CellType getTowerType() const override;
    void upgrade() override;
};


#endif //BOMBERTOWER_H
