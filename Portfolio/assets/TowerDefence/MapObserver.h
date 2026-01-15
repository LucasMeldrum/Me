#ifndef MAPOBSERVER_H
#define MAPOBSERVER_H

#include "Observer.h"
#include "Map.h"
#include "Subject.h"
#include <iostream>

class MapObserver : public Observer {
public:
    // Constructor attaches the observer to the provided map and prints a message.
    MapObserver(Map* m) : map(m) {
        if(map) {
            map->Attach(this);
            std::cout << "[MapObserver] Attached to Map." << std::endl;
        }
    }

    // Destructor detaches the observer from the map and prints a message.
    ~MapObserver() {
        if(map) {
            map->Detach(this);
            std::cout << "[MapObserver] Detached from Map." << std::endl;
        }
    }

    // Update method called when the map notifies its observers.
    void Update(Subject* subject) override {
        // Check that the update is coming from the correct subject
        if(subject == static_cast<Subject*>(map)) {
            std::cout << "\n[MapObserver] Map state changed. New map view:" << std::endl;
            map->displayMap();
            std::cout << "[MapObserver] Update complete." << std::endl;
        }
    }

private:
    Map* map;
};

#endif
