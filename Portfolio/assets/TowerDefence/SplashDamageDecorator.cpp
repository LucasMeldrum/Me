#include "SplashDamageDecorator.h"
#include "Critter.h"

SplashDamageDecorator::SplashDamageDecorator(Tower* tower) : TowerDecorator(tower) {}

void SplashDamageDecorator::applyEffect(Critter* critter) {
    // Base damage first
    TowerDecorator::applyEffect(critter);

    std::cout << "[SplashDecorator] Applying half damage to nearby critter.\n";

    // For each cell in this tower's range
    for (Cell* cell : cells) {
        if (cell && cell->isOccupiedByCritter()) {
            Critter* nearbyCritter = cell->getCritter();
            // If it is a different critter than the one we just hit
            if (nearbyCritter != critter) {
                nearbyCritter->takeDamage(getDamage() * 0.5f);
            }
        }
    }
}


