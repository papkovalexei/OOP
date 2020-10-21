#ifndef H_AIR_TRANSPORT
#define H_AIR_TRANSPORT

#include <string>

#include "Transport.h"

class AirTransport : public Transport
{
public:
    int getReducer() const;
    
    void setReducer(int coefficient);

    const char* getName() const override;
private:
    int _distance_reducer;
};

#endif
