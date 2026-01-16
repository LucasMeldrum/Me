#include "FastCritter.h"

FastCritter::FastCritter(Map* m, int startX, int startY)
    : Critter("Fast Critter", 3, m, startX, startY) {
    hitPoints = 40;
    speed = 2;  // Higher speed
    strength = 1;
    reward = 4;

}
