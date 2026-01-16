#ifndef TARGETING_STRATEGY_H
#define TARGETING_STRATEGY_H

#include <vector>
#include "Critter.h"

class TargetingStrategy {
public:
    virtual ~TargetingStrategy() = default;
    virtual Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) = 0;
    virtual std::string getName() const = 0;
};

class NearestToTowerStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override;
    std::string getName() const override { return "Nearest to Tower"; }
};

class NearestToExitStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override;
    std::string getName() const override { return "Nearest to Exit"; }
};

class StrongestCritterStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override;
    std::string getName() const override { return "Strongest Critter"; }
};

class WeakestCritterStrategy : public TargetingStrategy {
public:
    Critter* selectTarget(const std::vector<Critter*>& critters, Tower* tower) override;
    std::string getName() const override { return "Weakest Critter"; }
};

#endif