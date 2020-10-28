#ifndef H_TRANSPORT
#define H_TRANSPORT

#include <string>

class Transport
{
public:
    Transport();
    Transport(float speed, std::string name);
    
    float getSpeed() const;
    std::string getName() const;

    void setSpeed(float speed);
    void setName(std::string name);

    virtual float move(float distance);
protected:
    std::string _name;
    float _speed;
};

#endif