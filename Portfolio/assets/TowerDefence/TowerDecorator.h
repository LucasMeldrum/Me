#ifndef TOWERDECORATOR_H
#define TOWERDECORATOR_H

#include "Tower.h"

class TowerDecorator : public Tower {
protected:
    Tower* decoratedTower;

public:
    TowerDecorator(Tower* tower);
    virtual ~TowerDecorator();

    void checkRange() override;
    virtual void applyEffect(Critter* critter) = 0; // Each decorator will define its own effect

    CellType getTowerType() const override;
};

#endif // TOWERDECORATOR_H
