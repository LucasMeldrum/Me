#ifndef FREEZINGDAMAGEDECORATOR_H
#define FREEZINGDAMAGEDECORATOR_H

#include "TowerDecorator.h"

class FreezingDamageDecorator : public TowerDecorator {
public:
    FreezingDamageDecorator(Tower* tower);
    void applyEffect(Critter* critter) override;
};

#endif // FREEZINGDAMAGEDECORATOR_H
