#ifndef H_RACE_GRASS
#define H_RACE_GRASS

#include "Race.h"

class RaceGrass : public Race
{
public:
    RaceGrass();
    RaceGrass(float distance);

    void addTransport(Transport* transport) override;
private:
};

#endif