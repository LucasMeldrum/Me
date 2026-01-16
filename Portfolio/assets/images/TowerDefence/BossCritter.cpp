#include "BossCritter.h"

BossCritter::BossCritter(Map* m, int startX, int startY)
    : Critter("Boss Critter", 10, m, startX, startY) {
    hitPoints = 300;  // Massive HP
    speed = 3;
    strength = 3;
    reward = 50;

    shape.setPointCount(30);
    shape.setFillColor(sf::Color(0x2b0000ff));
}
