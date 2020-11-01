#ifndef H_STUPA
#define H_STUPA

#include "AirTransport.h"

class Stupa : public AirTransport
{
public:
    Stupa();

    float reducer(float distance) override;
};

#endif