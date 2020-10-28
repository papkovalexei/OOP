#ifndef H_RACE_AIR
#define H_RACE_AIR

#include "Race.h"

class RaceAir : public Race
{
public:
    RaceAir();
    RaceAir(float distance);

    void addTransport(Transport* transport) override;
private:
};

#endif