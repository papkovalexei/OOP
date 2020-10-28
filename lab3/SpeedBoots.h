#ifndef H_SPEED_BOOTS
#define H_SPEED_BOOTS

#include "GrassTransport.h"

class SpeedBoots : public GrassTransport
{
public:
    SpeedBoots();

    float move(float distance) override;
};

#endif