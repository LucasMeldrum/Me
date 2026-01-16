#ifndef RANDOM_TARGETING_STRATEGY_H
#define RANDOM_TARGETING_STRATEGY_H

#include "TargetingStrategy.h"

class RandomTargetingStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override {
        return critters[0];
    }

    std::string getName() const override {
        return "Random";
    }
};

#endif
