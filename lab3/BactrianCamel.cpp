#include "BactrianCamel.h"

BactrianCamel::BactrianCamel()
    : GrassTransport(10, 30, 5, "Bactrian camel")
{

}

float BactrianCamel::rest(float distance)
{
    float time = distance / _speed;
    float answer = 0;

    if (time >= _rest_interval)
    {
        answer = _rest_duration;
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