#include "MagicCarpet.h"

MagicCarpet::MagicCarpet()
    : AirTransport(10, 0, "Magic carpet")
{

}

float MagicCarpet::reducer(float distance)
{
    if (distance >= 1000.0 && distance <= 5000.0)
        _distance_reducer = 3;
    else if (distance >= 5000.0 && distance <= 10000.0)
        _distance_reducer = 10;
    else if (distance >= 10000.0)
        _distance_reducer = 5;
    else
        _distance_reducer = 0;
    
    return distance * (100.0 - _distance_reducer) / 100.0;
}