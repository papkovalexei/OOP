#include "Centaur.h"

Centaur::Centaur()
    : GrassTransport(15, 8, 2, "Centaur")
{

}

float Centaur::move(float distance)
{
    float now_pos = 0, time = 0, time_to_rest = 0;

    while (now_pos < distance)
    {
        now_pos += _speed;
        time++;
        time_to_rest++;

        if (time_to_rest >= _rest_interval)
        {
            time_to_rest = 0;
            time += _rest_duration;
        }
    }

    return time;
}