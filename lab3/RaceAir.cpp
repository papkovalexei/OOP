#include "RaceAir.h"

RaceAir::RaceAir()
{

}

RaceAir::RaceAir(float distance)
    : Race(distance)
{

}

void RaceAir::addTransport(Transport* transport)
{
    if (dynamic_cast<AirTransport*>(transport))
        _transport.push_back(transport);
    else
        throw Error::INCORRECT_TRANSPORT;
}