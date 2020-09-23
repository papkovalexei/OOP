#include "Item.h"

Item::Item()
    : _name(""), _uid(-1)
{

}

Item::Item(const std::string& name, const int& uid)
    : _name(name), _uid(uid)
{

}

int Item::getUID() const
{
    return _uid;
}