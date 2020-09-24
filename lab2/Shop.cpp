#include "Shop.h"

Shop::Shop()
    : _name(""), _address(""), _uid(-1)
{

}

Shop::Shop(const std::string& name, const std::string& address, const int& uid)
    : _name(name), _address(address), _uid(uid)
{

}

int Shop::getUID() const
{
    return _uid;
}

std::pair<Item, std::pair<int, int>>& Shop::getItems(const int& item_UID)
{    
    for (int i = 0; i < _items.size(); i++)
        if (_items[i].first.getUID() == item_UID)
            return _items[i];

    throw 1;
}

void Shop::addItem(const Item& item)
{
    std::pair<Item, std::pair<int, int>> buffer;

    buffer.first = item;
    buffer.second.first = 0;
    buffer.second.second = 0;

    _items.push_back(buffer);
}

void Shop::addItem(const Item& item, const int& count, const int& price)
{
    std::pair<Item, std::pair<int, int>> buffer;

    buffer.first = item;
    buffer.second.first = count;
    buffer.second.second = price;

    _items.push_back(buffer);
}

int Shop::getPriceItem(const int& item_UID) const
{
    for (auto it = _items.begin(); it != _items.end(); it++)
    {
        if ((*it).first.getUID() == item_UID && (*it).second.first > 0)
            return (*it).second.second;
    }
    return -1;
}

std::vector<std::pair<Item, std::pair<int, int>>> Shop::getAllItems() const
{
    return _items;
}