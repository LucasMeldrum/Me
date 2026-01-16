#include "TargetingStrategy.h"
#include <algorithm>
#include <limits>

#include "Tower.h"

Critter* NearestToTowerStrategy::selectTarget(const std::vector<Critter*>& critters, Tower* tower) {
    if (critters.empty()) return nullptr;

    return *std::min_element(critters.begin(), critters.end(),
        [tower](Critter* a, Critter* b) { return a->getDistanceToTower(tower->getPositionX(), tower->getPositionY()) < b->getDistanceToTower(tower->getPositionX(), tower->getPositionY()); });
}

Critter* NearestToExitStrategy::selectTarget(const std::vector<Critter*>& critters, Tower* tower) {
    if (critters.empty()) return nullptr;

    return *std::min_element(critters.begin(), critters.end(),
        [](Critter* a, Critter* b) { return a->getDistanceToExit() < b->getDistanceToExit(); });
}

Critter* StrongestCritterStrategy::selectTarget(const std::vector<Critter*>& critters, Tower* tower) {
    if (critters.empty()) return nullptr;

    return *std::max_element(critters.begin(), critters.end(),
        [](Critter* a, Critter* b) { return a->getHitPoints() < b->getHitPoints(); });
}

Critter* WeakestCritterStrategy::selectTarget(const std::vector<Critter*>& critters, Tower* tower) {
    if (critters.empty()) return nullptr;

    return *std::min_element(critters.begin(), critters.end(),
        [](Critter* a, Critter* b) { return a->getHitPoints() < b->getHitPoints(); });
}