#ifndef H_SPEED_CAMEL
#define H_SPEED_CAMEL

#include "GrassTransport.h"

class SpeedCamel : public GrassTransport
{
public:
    SpeedCamel();

    float move(float distance) override;
};

#endif