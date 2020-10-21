#include "Transport.h"

Transport::Transport()
    : _speed(-1)
{

}

Transport::Transport(int speed)
    : _speed(speed)
{

}

int Transport::getSpeed() const
{
    return _speed;
}

std::string Transport::getName() const
{
    return _name;
}

void Transport::setSpeed(int speed)
{
    this->_speed = speed;
}

void Transport::setName(std::string name)
{
    this->_name = name;
}