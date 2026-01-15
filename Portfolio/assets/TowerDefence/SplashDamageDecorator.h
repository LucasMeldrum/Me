#ifndef SPLASHDAMAGEDECORATOR_H
#define SPLASHDAMAGEDECORATOR_H

#include "TowerDecorator.h"

class SplashDamageDecorator : public TowerDecorator {
public:
    SplashDamageDecorator(Tower* tower);
    void applyEffect(Critter* critter) override;
};

#endif // SPLASHDAMAGEDECORATOR_H
