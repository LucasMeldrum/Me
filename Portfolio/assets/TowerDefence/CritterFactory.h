#ifndef CRITTER_FACTORY_H
#define CRITTER_FACTORY_H

#include "Critter.h"
#include <memory>  // For smart pointers

class CritterFactory {
public:
    static std::shared_ptr<Critter> createCritter(int waveNumber, Map* map, int startX, int startY);
};

#endif // CRITTER_FACTORY_H
