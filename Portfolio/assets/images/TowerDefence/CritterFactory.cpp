#include "CritterFactory.h"
#include "WeakCritter.h"
#include "FastCritter.h"
#include "StrongCritter.h"
#include "BossCritter.h"
#include <random>

std::shared_ptr<Critter> CritterFactory::createCritter(int waveNumber, Map* map, int startX, int startY) {
    // Seed the random number generator
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Define probabilities for critter types (these probabilities could change based on waveNumber)
    std::uniform_int_distribution<> dist(1, 100);

    int chance = dist(gen); // Random number between 1 and 100

    // Wave 5: Only BossCritters (100% chance for BossCritter)
    if (waveNumber == 5) {
        return std::make_shared<BossCritter>(map, startX, startY);
    }

    // For waves other than 5
    if (waveNumber == 1) {
        // Wave 1: Only WeakCritters
        return std::make_shared<WeakCritter>(map, startX, startY);
    } else if (waveNumber == 2) {
        // Wave 2: Mix of WeakCritters (50%) and StrongCritters (50%)
        if (chance <= 50) {
            return std::make_shared<WeakCritter>(map, startX, startY);
        } else {
            return std::make_shared<StrongCritter>(map, startX, startY);
        }
    } else if (waveNumber == 3) {
        // Wave 3: Only FastCritters
        return std::make_shared<FastCritter>(map, startX, startY);
    } else if (waveNumber == 4) {
        // Wave 4: Mix of WeakCritters (50%) and StrongCritters (50%)
        if (chance <= 50) {
            return std::make_shared<FastCritter>(map, startX, startY);
        } else {
            return std::make_shared<BossCritter>(map,
            startX, startY);
        }
    }

    // If none of the above conditions matched, return nullptr (this should never happen due to our conditions)
    return nullptr;
}
