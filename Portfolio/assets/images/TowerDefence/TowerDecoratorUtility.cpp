#include "TowerDecoratorUtility.h"
#include "SplashDamageDecorator.h"
#include "BurningDamageDecorator.h"
#include "FreezingDamageDecorator.h"

void applyDecorator(Tower*& tower, const std::string& upgradeType) {
    if (upgradeType == "splash") {
        tower = new SplashDamageDecorator(tower);
    } else if (upgradeType == "burning") {
        tower = new BurningDamageDecorator(tower);
    } else if (upgradeType == "freezing") {
        tower = new FreezingDamageDecorator(tower);
    }
}

