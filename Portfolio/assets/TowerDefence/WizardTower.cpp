//
// Created by kfrai on 2025-02-15.
//

#include "WizardTower.h"

std::string WizardTower::wName = "Wizard Tower";
int WizardTower::wMaxLevel = 4;
float WizardTower::wPrice = 350;
int WizardTower::wRange = 3;
float WizardTower::wDamage = 30;
float WizardTower::wRoF = 1;

WizardTower::WizardTower(Player *player, int x, int y)
    : Tower(x, y, player, wName, wMaxLevel, wPrice, wRange, wDamage, wRoF) {
    damageUpgrade = 20;
    RoFUpgrade = 0;
    rangeUpgrade = 1;
}


CellType WizardTower::getTowerType() const {
    return WIZARDTOWER;
}

void WizardTower::critterProtocol(Critter *critter) {
    Tower::critterProtocol(critter);
}
