#ifndef H_BACTRIAN_CAMEL
#define H_BACTRIAN_CAMEL

#include "GrassTransport.h"

class BactrianCamel : public GrassTransport
{
public:
    BactrianCamel();

    float rest(float distance) override;
};

#endif