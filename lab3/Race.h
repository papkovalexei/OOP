#ifndef H_RACE
#define H_RACE

#include <vector>

#include "Transport.h"

class Race
{
public:
    enum RaceType
    {
        AllGrassRace,
        AllAirRace,
        SemiAirGrassRace
    };

    Race();
    Race(RaceType type, int distance);

    void setRaceType(RaceType type);

    RaceType getRaceType() const;

    void addTransport(const Transport* transport);
    Transport run() const;

private:
    bool checkValidNewTransport(const Transport* transport);

    int _distance;
    RaceType _type;
    std::vector<Transport*> _transport;
};

#endif