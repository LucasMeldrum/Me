#ifndef STRONGEST_TARGETING_STRATEGY_H
#define STRONGEST_TARGETING_STRATEGY_H

#include "TargetingStrategy.h"

class StrongestTargetingStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override {
        // Simplified for illustration: select the first critter (you can implement actual logic)
        return critters[0];
    }

    std::string getName() const override {
        return "Strongest";
    }
};

#endif
