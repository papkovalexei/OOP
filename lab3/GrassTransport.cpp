#include "GrassTransport.h"

GrassTransport::GrassTransport(float speed, float rest_interval, float rest_duration, std::string name)
    : Transport(speed, name), _rest_duration(rest_duration), _rest_interval(rest_interval)
{

}

float GrassTransport::getRestInterval() const
{
    return _rest_interval;
}

float GrassTransport::getRestDuration() const
{
    return _rest_duration;
}

void GrassTransport::setRestInterval(float rest_interval)
{
    _rest_interval = rest_interval;
}

void GrassTransport::setRestDuration(float rest_duration)
{
    _rest_duration = rest_duration;
}