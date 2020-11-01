#include "SpeedCamel.h"

SpeedCamel::SpeedCamel()
    : GrassTransport(40, 10, 5, "Speed camel")
{

}

float SpeedCamel::rest(float distance)
{
    float time = distance / _speed;
    float answer = 0;

    if (time >= _rest_interval)
    {
        answer = _rest_duration;
        _rest_duration = 6.5;
        time -= _rest_interval;
    }
    
    if (time >= _rest_interval)
    {
        answer += _rest_duration;
        _rest_duration = 8;
        time -= _rest_interval;
    }

    if (time >= _rest_interval)
    {
        time = (int)time - ((int)time % (int)_rest_interval);

        answer += _rest_duration * (time / _rest_interval);
    }
    return answer;
}