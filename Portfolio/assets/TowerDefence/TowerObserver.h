#ifndef TOWEROBSERVER_H
#define TOWEROBSERVER_H

#include <iostream>
#include <string>

class TowerObserver {
public:
    virtual ~TowerObserver() = default;
    virtual void onTowerUpdate(const std::string& message) = 0;
};

class ConcreteTowerObserver : public TowerObserver {
public:
    void onTowerUpdate(const std::string& message) override;
};

#endif