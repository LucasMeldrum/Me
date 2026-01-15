#include "BurningDamageDecorator.h"
#include "Critter.h"

BurningDamageDecorator::BurningDamageDecorator(Tower* tower) : TowerDecorator(tower) {
    std::cout << "[BurningDamageDecorator] CONSTRUCTOR called.\n";
}

void BurningDamageDecorator::applyEffect(Critter* critter) {
    TowerDecorator::applyEffect(critter); // base damage
    std::cout << "[BurningDecorator] Applying burn damage now...\n";
    // e.g., in BurningDamageDecorator
    std::cout << "[BurningDamageDecorator] Changing critter color to Red!\n";
    critter->getShape()->setFillColor(sf::Color::Red);




    // Inflict burn damage over time
    for (int i = 0; i < 3; i++) {
        critter->takeDamage(this->getDamage() * 0.3);
        std::cout << "[BurningDecorator] Dealt "
                  << (this->getDamage() * 0.3)
                  << " burn damage on iteration " << i << "\n";
    }
}