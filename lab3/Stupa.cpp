#include "Stupa.h"

Stupa::Stupa()
    : AirTransport(8, 6, "Stupa")
{

}

float Stupa::move(float distance)
{
    float now_pos = 0, time = 0;

    distance *= (100.0 - _distance_reducer) / 100.0;

    while (now_pos < distance)
    {

        time++;
        now_pos += _speed;
    }

    return time;
}