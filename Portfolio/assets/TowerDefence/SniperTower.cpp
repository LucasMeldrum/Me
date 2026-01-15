//
// Created by kfrai on 2025-02-15.
//

#include "SniperTower.h"

#include "Cell.h"
#include "Critter.h"
#include "Map.h"

std::string SniperTower::sName = "Sniper Tower";
int SniperTower::sMaxLevel = 4;
float SniperTower::sPrice = 500;
int SniperTower::sRange = 5;
float SniperTower::sDamage = 80;
float SniperTower::sRoF = 5;


SniperTower::SniperTower(Player *player, int x, int y): Tower(x, y, player, sName, sMaxLevel, sPrice, sRange, sDamage,
                                                              sRoF) {
}


void SniperTower::upgrade() {
    if (getLevel() < getMaxLevel()) {
        std::cout << "Upgrading Sniper Tower with a burning-like effect!\n";

        // Example: drastically increase damage before base logic
        setDamage(getDamage() + 15.0f);
        Tower::upgrade();
    } else {
        std::cout << "Sniper Tower is already at max level.\n";
    }
}


CellType SniperTower::getTowerType() const {
    return SNIPERTOWER;
}


void SniperTower::critterProtocol(Critter* critter) {
    Tower::critterProtocol(critter);
    // normal direct damage

    if (this->getLevel() > 1) {
                // If it’s still alive, apply burning
        if (!critter->isDead()) {
            critter->setBurning(3, 5);
            // 3 ticks of burning, 5 damage each
        }
    }
}
