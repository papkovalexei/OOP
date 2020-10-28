#include "MagicCarpet.h"

MagicCarpet::MagicCarpet()
    : AirTransport(10, 0, "Magic carpet")
{

}

float MagicCarpet::move(float distance)
{
    float now_pos = 0, time = 0;

    if (distance >= 1000.0 && distance <= 5000.0)
        _distance_reducer = 3;
    else if (distance >= 5000.0 && distance <= 10000.0)
        _distance_reducer = 10;
    else if (distance >= 10000.0)
        _distance_reducer = 5;
    else
        _distance_reducer = 0;
    
    distance *= (100.0 - _distance_reducer) / 100.0;

    while (now_pos < distance)
    {
        time++;
        now_pos += _speed;
    }

    return time;
}