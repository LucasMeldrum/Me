//
// Created by kfrai on 2025-02-15.
//

#ifndef WIZARDTOWER_H
#define WIZARDTOWER_H
#include "Tower.h"


class WizardTower : public Tower {
private:


public:
    static std::string wName;
    static int wMaxLevel;
    static float wPrice;
    static int wRange;
    static float wDamage;
    static float wRoF;

    WizardTower(Player *player, int x, int y);


    void critterProtocol(Critter *critter) override;

    CellType getTowerType() const override;
};


#endif //WIZARDTOWER_H
