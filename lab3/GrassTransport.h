#ifndef H_GRASS_TRANSPORT
#define H_GRASS_TRANSPORT

#include <string>

#include "Transport.h"

class GrassTransport : public Transport
{
public:
    GrassTransport(float speed, float rest_interval, float rest_duration, std::string name);

    ~GrassTransport();

    float getRestInterval() const;
    float getRestDuration() const;

    void setRestInterval(float rest_interval);
    void setRestDuration(float rest_duration);

    virtual float rest(float distance) = 0;
    float move(float distance) override;
protected:
    float _rest_interval;
    float _rest_duration;
};

#endif