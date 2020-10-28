#include "Broom.h"

Broom::Broom()
    : AirTransport(20, 1, "Broom")
{

}

float Broom::move(float distance)
{
    float now_pos = 0, time = 0, delta = 0;

    while (now_pos < distance)
    {

        time++;
        now_pos += _speed;
        delta += _speed;

        if (delta > 1000.0)
        {
            distance *= (100.0 - _distance_reducer) / 100.0;
            delta = 0;
        }
    }

    return time;
}