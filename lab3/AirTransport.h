#ifndef H_AIR_TRANSPORT
#define H_AIR_TRANSPORT

#include <string>

#include "Transport.h"

class AirTransport : public Transport
{
public:
    AirTransport(float speed, float distance_reducer, std::string name);

    float getReducer() const;
    
    void setReducer(float distance_reducer);
protected:
    float _distance_reducer;
};

#endif