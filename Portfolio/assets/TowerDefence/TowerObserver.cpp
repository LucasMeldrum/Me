#include "TowerObserver.h"
#include <iostream>

void ConcreteTowerObserver::onTowerUpdate(const std::string& message) {
    std::cout << "Observer tower update: " << message << std::endl;
}