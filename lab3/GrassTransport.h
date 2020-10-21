#ifndef H_GRASS_TRANSPORT
#define H_GRASS_TRANSPORT

#include <string>

#include "Transport.h"

class GrassTransport : public Transport
{
    int getRestInterval() const;
    int getRestDuration() const;

    void setRestInterval(int rest_interval);
    void setRestDuration(int rest_duration);
private:
    int _rest_interval;
    int _rest_duration;
};

#endif