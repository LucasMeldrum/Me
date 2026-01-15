#ifndef BURNINGDAMAGEDECORATOR_H
#define BURNINGDAMAGEDECORATOR_H

#include "TowerDecorator.h"

class BurningDamageDecorator : public TowerDecorator {
public:
    BurningDamageDecorator(Tower* tower);
    void applyEffect(Critter* critter) override;
};

#endif // BURNINGDAMAGEDECORATOR_H
