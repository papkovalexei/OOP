#ifndef H_MAGIC_CARPET
#define H_MAGIC_CARPET

#include "AirTransport.h"

class MagicCarpet : public AirTransport
{
public:
    MagicCarpet();

    float reducer(float distance) override;
};

#endif