#ifndef H_CENTAUR
#define H_CENTAUR

#include "GrassTransport.h"

class Centaur : public GrassTransport
{
public:
    Centaur();

    float rest(float distance) override;
};

#endif