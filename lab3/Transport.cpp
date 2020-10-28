#include "Transport.h"

Transport::Transport()
    : _speed(-1)
{

}

Transport::Transport(float speed, std::string name)
    : _speed(speed), _name(name)
{

}

float Transport::getSpeed() const
{
    return _speed;
}

std::string Transport::getName() const
{
    return _name;
}

void Transport::setSpeed(float speed)
{
    this->_speed = speed;
}

void Transport::setName(std::string name)
{
    this->_name = name;
}

float Transport::move(float distance)
{
    return 0;
}