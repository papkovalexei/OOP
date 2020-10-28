#ifndef H_STUPA
#define H_STUPA

#include "AirTransport.h"

class Stupa : public AirTransport
{
public:
    Stupa();

    float move(float distance) override;
};

#endif