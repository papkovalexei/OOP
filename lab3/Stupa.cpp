#include "Stupa.h"

Stupa::Stupa()
    : AirTransport(8, 6, "Stupa")
{

}

float Stupa::reducer(float distance)
{
    return distance * (100 - _distance_reducer) / 100.0;
}