#include "FreezingDamageDecorator.h"
#include <iostream>
#include "Critter.h"


FreezingDamageDecorator::FreezingDamageDecorator(Tower* tower) : TowerDecorator(tower) {}

void FreezingDamageDecorator::applyEffect(Critter* critter) {
    TowerDecorator::applyEffect(critter);
    std::cout << "[FreezingDecorator] Reducing speed by 50%\n";

    // Then reduce the critter's speed:
    critter->reduceSpeed(0.5f);
}
