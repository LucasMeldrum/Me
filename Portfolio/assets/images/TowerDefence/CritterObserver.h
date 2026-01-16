#ifndef CRITTEROBSERVER_H
#define CRITTEROBSERVER_H

#include "Observer.h"
#include "Critter.h"
#include "Subject.h"
#include <iostream>

class CritterObserver : public Observer {
public:
    // Constructor attaches the observer to the provided critter
    CritterObserver(Critter* c) : critter(c) {
        if (critter) {
            critter->Attach(this);
            std::cout << "[CritterObserver] Attached to Critter: " << critter->getName() << std::endl;
        }
    }

    // Destructor detaches the observer
    ~CritterObserver() {
        if (critter) {
            critter->Detach(this);
            std::cout << "[CritterObserver] Detached from Critter: " << critter->getName() << std::endl;
        }
    }

    // Update method definition (no need for extra qualification)
    void Update(Subject* subject) override {
        if (subject == static_cast<Subject*>(critter)) {
            std::cout << "[CritterObserver] Update received for Critter: " << critter->getName() << std::endl;
            critter->display();

            // Now you can access the map through the Critter instance
            Map* map = critter->getMap();  // Access map through critter

            // Check if the critter reached the exit
            if (critter->getX() == map->getExitX() && critter->getY() == map->getExitY()) {
                critter->Detach(this);  // Detach only this observer
                std::cout << "[CritterObserver] Detached from critter at exit: " << critter->getName() << std::endl;
            }

            // Alternatively, if the critter is dead, detach the observer
            if (critter->isDead()) {
                critter->Detach(this);  // Detach only this observer
                std::cout << "[CritterObserver] Detached from dead Critter: " << critter->getName() << std::endl;
            }
        }
    }

private:
    Critter* critter;
};

#endif
