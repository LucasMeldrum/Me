#ifndef FASTCRITTER_H
#define FASTCRITTER_H

#include "Critter.h"

class FastCritter : public Critter {
public:
    FastCritter(Map* m, int startX, int startY);
};

#endif // FASTCRITTER_H
