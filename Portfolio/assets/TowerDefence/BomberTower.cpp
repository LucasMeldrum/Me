//
// Created by kfrai on 2025-02-14.
//

#include "BomberTower.h"
#include "Map.h"
#include "Cell.h"
#include "Critter.h"
#include "SplashDamageDecorator.h"


std::string BomberTower::bName = "Bomber Tower";
int BomberTower::bMaxLevel = 4;
float BomberTower::bPrice = 500;
int BomberTower::bRange = 2;
float BomberTower::bDamage = 15;
float BomberTower::bRoF = 3;

BomberTower::BomberTower(Player *player, int x, int y)
    : Tower(x, y, player, bName, bMaxLevel, bPrice, bRange, bDamage, bRoF) {
}

CellType BomberTower::getTowerType() const {
    return BOMBERTOWER;
}

void BomberTower::critterProtocol(Critter* critter) {
    Tower::critterProtocol(critter);
}

void BomberTower::upgrade() {
    if (getLevel() < getMaxLevel()) {
        std::cout << "Upgrading Bomber Tower with splash-like effect!\n";
        setDamage(getDamage() + 5.0f);
        Tower::upgrade();
    } else {
        std::cout << "Bomber Tower is already at max level.\n";
    }
}
