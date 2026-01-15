#ifndef NEAREST_TARGETING_STRATEGY_H
#define NEAREST_TARGETING_STRATEGY_H

#include "TargetingStrategy.h"
#include "Tower.h"

class NearestTargetingStrategy : public TargetingStrategy  {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override {
        return critters.empty() ? nullptr :
               *std::min_element(critters.begin(), critters.end(),
               [tower](Critter* a, Critter* b) { return a->getDistanceToTower(tower->getPositionX(), tower->getPositionY()) < b->getDistanceToTower(tower->getPositionX(), tower->getPositionY()); });
    }

    std::string getName() const override {
        return "Nearest";
    }
};

#endif 