#ifndef H_BROOM
#define H_BROOM

#include "AirTransport.h"

class Broom : public AirTransport
{
public:
    Broom();

    float move(float distance) override;
};

#endif