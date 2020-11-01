#include "AirTransport.h"

AirTransport::AirTransport(float speed, float distance_reducer, std::string name)
    : Transport(speed, name), _distance_reducer(distance_reducer)
{
    if (distance_reducer < 0)
    {
        this->~AirTransport();
        throw Error::INCORRECT_REDUCER;
    }
}

AirTransport::~AirTransport()
{

}

float AirTransport::getReducer() const
{
    return _distance_reducer;
}

void AirTransport::setReducer(float distance_reducer)
{
    _distance_reducer = distance_reducer;
}

float AirTransport::move(float distance)
{
    distance = reducer(distance);

    return distance / _speed;
}