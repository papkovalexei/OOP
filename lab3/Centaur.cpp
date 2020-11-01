#include "Centaur.h"

Centaur::Centaur()
    : GrassTransport(15, 8, 2, "Centaur")
{

}

float Centaur::rest(float distance)
{
    float time = distance / _speed;

    if (time >= 8)
    {
        time = (int)time - ((int)time % (int)_rest_interval);

        return _rest_duration * (time / _rest_interval); 
    }

    return 0;
}