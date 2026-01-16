#ifndef BOSSCRITTER_H
#define BOSSCRITTER_H

#include "Critter.h"

class BossCritter : public Critter {
public:
    BossCritter(Map* m, int startX, int startY);
};

#endif // BOSSCRITTER_H
