//
// Created by kfrai on 2025-03-20.
//

#ifndef CRITTERSTATS_H
#define CRITTERSTATS_H
#include <string>
#include <vector>

class Critter;


class CritterStats {
    std::string baseString;
    static std::vector<Critter*> critters;

public:
    CritterStats(const std::string &baseString);
    ~CritterStats();

    static void addNewCritter(Critter* critter);

    static void removeCritter(const Critter *critter);

    std::string critterToString(Critter *critter);

    std::string update();
};



#endif //CRITTERSTATS_H
