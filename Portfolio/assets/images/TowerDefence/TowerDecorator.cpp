#include "TowerDecorator.h"


class Tower;

TowerDecorator::TowerDecorator(Tower* tower) : Tower(tower), decoratedTower(tower) {}

TowerDecorator::~TowerDecorator() {
    delete decoratedTower;
}

void TowerDecorator::checkRange() {
    decoratedTower->checkRange();
}

CellType TowerDecorator::getTowerType() const {
    return decoratedTower->getTowerType();
}
void TowerDecorator::applyEffect(Critter* critter) {
    if (decoratedTower) {
        decoratedTower->applyEffect(critter);
    }
}
