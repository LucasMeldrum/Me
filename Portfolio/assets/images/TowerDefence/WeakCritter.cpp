#include "WeakCritter.h"

WeakCritter::WeakCritter(Map* m, int startX, int startY)
    : Critter("Weak Critter", 1, m, startX, startY) {
    hitPoints = 30;
    speed = 1;
    strength = 1;
    reward = 2;

    shape.setRadius(10);
    shape.setPointCount(4);
    shape.setFillColor(sf::Color(0x962f2fff));
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(3);
}
