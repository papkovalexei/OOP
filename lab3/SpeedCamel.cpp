#include "SpeedCamel.h"

SpeedCamel::SpeedCamel()
    : GrassTransport(40, 10, 5, "Bactrian camel")
{

}

float SpeedCamel::move(float distance)
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

            if (_rest_duration == 5)
                _rest_duration = 6.5;
            else if (_rest_duration == 6.5)
                _rest_duration = 8;
        }
    }

    return time;
}