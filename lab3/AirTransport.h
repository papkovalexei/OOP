#ifndef H_AIR_TRANSPORT
#define H_AIR_TRANSPORT

#include <string>

#include "Transport.h"

class AirTransport : public Transport
{
public:
    AirTransport(float speed, float distance_reducer, std::string name);

    ~AirTransport();

    float getReducer() const;
    
    void setReducer(float distance_reducer);

    virtual float reducer(float distance) = 0;
    float move(float distance) override;

protected:
    float _distance_reducer;
};

#endif