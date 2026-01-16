//
// Created by kfrai on 2025-03-20.
//

#ifndef TOWERSTATS_H
#define TOWERSTATS_H
#include <string>
#include <vector>

class Tower;


class TowerStats {
    std::string baseString;
    static std::vector<Tower*> towers;

    public:
    TowerStats(const std::string &baseString);
    ~TowerStats();

    static void addNewTower(Tower* tower);

    static void removeTower(const Tower* tower);

    std::string towerToString(Tower *tower);

    std::string update();
};



#endif //TOWERSTATS_H
