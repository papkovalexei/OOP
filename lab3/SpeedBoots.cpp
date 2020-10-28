#include "SpeedBoots.h"

SpeedBoots::SpeedBoots()
    : GrassTransport(6, 60, 10, "Speed boots")
{

}

float SpeedBoots::move(float distance)
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
            _rest_duration = 5;
        }
    }

    return time;
}