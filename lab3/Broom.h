#ifndef H_BROOM
#define H_BROOM

#include "AirTransport.h"

class Broom : public AirTransport
{
public:
    Broom();

    float reducer(float distance) override;
};

#endif