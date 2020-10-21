#ifndef H_TRANSPORT
#define H_TRANSPORT

#include <string>

class Transport
{
public:
    Transport();
    Transport(int speed);
    
    int getSpeed() const;
    std::string getName() const;

    void setSpeed(int speed);
    void setName(std::string name);
private:
    std::string _name;
    int _speed;
};

#endif