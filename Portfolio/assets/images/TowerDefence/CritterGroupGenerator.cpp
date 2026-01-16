#include "crittergroupgenerator.h"
#include "CritterFactory.h"
#include "CritterObserver.h"

// Constructor to initialize the CritterGroupGenerator with a map and number of critters per wave
CritterGroupGenerator::CritterGroupGenerator(Map* m, int crittersPerWave)
    : map(m), waveNumber(0), crittersPerWave(crittersPerWave) {
    // The map and number of critters per wave are initialized here
    // waveNumber starts from 0 and will be incremented for each new wave
}

// Method to spawn a new wave of critters
void CritterGroupGenerator::spawnWave() {
    waveNumber++; // Increment the wave number to represent the next wave
    CritterFactory factory; // Create a factory instance to generate critters

    // Loop through the number of critters to spawn for this wave
    for (int i = 0; i < crittersPerWave; i++) {
        // Use the factory to create the appropriate critter based on the wave number
        auto critter = factory.createCritter(waveNumber, map, 0, 0);

        // Attach an observer to the created critter
        // The observer will automatically listen for updates or changes to the critter
        new CritterObserver(critter.get());  // Observer automatically attaches to critter

        // Add the newly created critter to the critters list
        // std::move is used to efficiently transfer ownership of the critter object
        critters.push_back(std::move(critter));
    }
}

// Method to update the critters in the current wave
void CritterGroupGenerator::update() {
    // Iterate through the list of critters
    for (auto it = critters.begin(); it != critters.end();) {
        // Move the critter according to its behavior (this includes any logic like movement)
        (*it)->move();

        // Check if the critter is dead or has reached the exit
        if ((*it)->isDead() || ((*it)->getX() == map->getExitX() && (*it)->getY() == map->getExitY())) {
            // If dead or at the exit, remove the critter from the list
            it = critters.erase(it); // Erase returns the next iterator, preventing invalidated iterator errors
        } else {
            ++it; // Otherwise, continue to the next critter
        }
    }
}

// Method to display all the critters' information
void CritterGroupGenerator::displayCritters() const {
    // Loop through each critter in the list and display its details
    for (const auto& critter : critters) {
        critter->display(); // Display the critter's information
    }
}

// Method to check if the wave has been cleared (i.e., if all critters are dead or reached the exit)
bool CritterGroupGenerator::isWaveCleared() const {
    // If the critters list is empty, then the wave has been cleared
    return critters.empty();
}
