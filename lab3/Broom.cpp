#include "Broom.h"

Broom::Broom()
    : AirTransport(20, 1, "Broom")
{

}

float Broom::reducer(float distance)
{
    float answer = distance;

    while (distance > 0)
    {
        distance -= 1000;

        if (distance > 0)
            answer *= (100 - _distance_reducer) / 100.0;   
    }

    return answer;
}