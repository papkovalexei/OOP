#ifndef H_RACE
#define H_RACE

#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iostream>

#include "Transport.h"

#include "AirTransport.h"
#include "GrassTransport.h"

#include "Error.h"

class Race
{
public:
    Race();
    Race(float distance);

    ~Race();

    float getDistance() const;

    void setDistance(float distance);

    virtual void addTransport(Transport* transport);
    virtual std::vector<Transport*> run();

protected:
    std::vector<Transport*> _transport;
    float _distance;

    const float DISTANCE = 100;
};

#endif