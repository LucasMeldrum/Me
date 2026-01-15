#ifndef CRITTERGROUPGENERATOR_H
#define CRITTERGROUPGENERATOR_H

#include "Critter.h"
#include "Map.h"
#include <vector>
#include <memory>
#include <iostream>

class CritterGroupGenerator {
private:
    std::vector<std::shared_ptr<Critter>> critters;
    Map* map;
    int waveNumber;
    int crittersPerWave;

public:
    CritterGroupGenerator(Map* m, int crittersPerWave);
    void spawnWave();
    void update();
    void displayCritters() const;
    bool isWaveCleared() const;
};

#endif // CRITTERGROUPGENERATOR_H
