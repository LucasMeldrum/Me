#include "StrongCritter.h"

StrongCritter::StrongCritter(Map* m, int startX, int startY)
    : Critter("Strong Critter", 5, m, startX, startY) {
    hitPoints = 100;  // High HP
    speed = 1;        // Slow
    strength = 2;
    reward = 10;

    shape.setRotation(sf::degrees(45.0f));
    shape.setFillColor(sf::Color(0xc90000ff));
}
