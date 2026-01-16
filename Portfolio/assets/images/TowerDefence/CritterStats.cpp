//
// Created by kfrai on 2025-03-20.
//

#include "CritterStats.h"

#include "Critter.h"


std::vector<Critter*> CritterStats::critters;

CritterStats::CritterStats(const std::string &baseString) : baseString(baseString) {
}

CritterStats::~CritterStats() {
}

void CritterStats::addNewCritter(Critter* critter) {
    critters.push_back(critter);
}

void CritterStats::removeCritter(const Critter* critter) {
    for (auto it = critters.begin(); it != critters.end(); ++it) {
        if (*it == critter) {
            critters.erase(it);
            return;
        }
    }
}

std::string CritterStats::critterToString(Critter* critter) {
    return critter->getName() + ": " + std::to_string(critter->getHitPoints()) +"HP\n";
}

std::string CritterStats::update() {
    std::string newString = baseString + "\n";
    int index = 1;
    for (auto it = critters.begin(); it != critters.end(); ++it, ++index) {
        newString += std::to_string(index) + ". " + critterToString(*it) + "\n";
    }
    return newString;
}