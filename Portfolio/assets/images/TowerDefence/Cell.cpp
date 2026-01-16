#include "Cell.h"

#include <iostream>

float Cell::cellSize = 50.f;

Cell::Cell(int x, int y, CellType type) : x(x), y(y), cellType(type), inRangeOfTower(false) {

    BT = sf::Color(0xDD905Fff);
    ST = sf::Color(0x44598Cff);
    WT = sf::Color(0xEB7571ff);

    shape.setSize({cellSize, cellSize});
    shape.setOutlineColor(sf::Color(255, 255, 255));
    shape.setOutlineThickness(3.f);
    if (cellType == PATH || cellType == ENTRY || cellType == EXIT) {
        backgroundColor = sf::Color(0x493D30ff);
    }
    else {
        backgroundColor = sf::Color(0x679865ff);
    }
    shape.setFillColor(backgroundColor);

    BTicon.setRadius(23);
    BTicon.setFillColor(BT);
    BTicon.setOutlineColor(sf::Color::White);
    BTicon.setOutlineThickness(3);

    STicon.setRadius(23);
    STicon.setFillColor(ST);
    STicon.setOutlineColor(sf::Color::White);
    STicon.setOutlineThickness(3);
    STicon.setPointCount(3);

    WTicon.setRadius(23);
    WTicon.setFillColor(WT);
    WTicon.setOutlineColor(sf::Color::White);
    WTicon.setOutlineThickness(3);
    WTicon.setPointCount(5);

    tower = nullptr;

}

Tower * Cell::getTower() {
    return tower;
}

void Cell::setTower(Tower *towerNew) {
    tower = towerNew;
}

void Cell::setInRangeOfTower(bool inRangeOfTower) {
    this->inRangeOfTower = inRangeOfTower;
}

CellType Cell::getCellType() {
    return cellType;
}

int Cell::getPosX() {
    return x;
}

int Cell::getPosY() {
    return y;
}

sf::Color Cell::getBackgroundColor() {
    return backgroundColor;
}

void Cell::setBackgroundColor(sf::Color c) {
    backgroundColor = c;
}

Critter * Cell::getCritter() {
    return occupiedByCritter;
}

void Cell::setCritter(Critter *critter) {
    occupiedByCritter = critter;
}

void Cell::removeCritter() {
    occupiedByCritter = nullptr;
}

bool Cell::isOccupiedByCritter() const {
    return occupiedByCritter != nullptr;
}

int Cell::getPoxY() {
    return y;
}
