#include "RaceGrass.h"

RaceGrass::RaceGrass()
{

}

RaceGrass::RaceGrass(float distance)
    : Race(distance)
{

}

void RaceGrass::addTransport(Transport* transport)
{
    if (dynamic_cast<GrassTransport*>(transport))
        _transport.push_back(transport);
    else
        throw Error::INCORRECT_TRANSPORT;
}