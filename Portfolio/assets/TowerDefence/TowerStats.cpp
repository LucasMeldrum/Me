//
// Created by kfrai on 2025-03-20.
//

#include "TowerStats.h"

#include "Tower.h"

std::vector<Tower*> TowerStats::towers;

TowerStats::TowerStats(const std::string &baseString) : baseString(baseString){
}

TowerStats::~TowerStats() {
}

void TowerStats::addNewTower(Tower *tower) {
    towers.push_back(tower);
}

void TowerStats::removeTower(const Tower *tower) {
    for (auto it = towers.begin(); it != towers.end(); ++it) {
        if (*it == tower) {
            towers.erase(it);
            return;
        }
    }
}

std::string TowerStats::towerToString(Tower *tower) {
    return tower->getName() + ": Level " + std::to_string(tower->getLevel()) + ", Strategy: " + tower->getStrat() + "\n";
}

std::string TowerStats::update() {
    std::string newString = baseString + "\n";
    int index = 1;
    for (auto it = towers.begin(); it != towers.end(); ++it, ++index) {
        newString += std::to_string(index) + ". " + towerToString(*it) + "\n";
    }
    return newString;
}
