#ifndef WEAKCRITTER_H
#define WEAKCRITTER_H

#include "Critter.h"

class WeakCritter : public Critter {
public:
    WeakCritter(Map* m, int startX, int startY);
};

#endif // WEAKCRITTER_H
