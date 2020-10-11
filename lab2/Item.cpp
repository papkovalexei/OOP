#include "Item.h"

Item::Item()
{

}

Item::Item(const std::string& name, const int uid)
    : _name(name), _uid(uid)
{

}

bool Item::operator<(const Item& other) const
{
    return this->_uid < other._uid;
}