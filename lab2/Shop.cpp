#include "Shop.h"

Shop::Shop()
{

}

Shop::Shop(const std::string& name, const std::string& address, const int uid)
    : _name(name), _address(address), _uid(uid)
{

}

const std::map<Item, std::pair<int, int>>& Shop::getAllItem() const
{
    return _items;
}

int Shop::getUID() const
{
    return _uid;
}

int Shop::getPriceItem(const Item& item) const
{
    if (_items.count(item) == 0)
        return -1;
    return const_cast<std::map<Item, std::pair<int, int>>&>(_items)[item].second;
}

void Shop::shipment(const Item& item, const int count, const int price)
{
    _items[item].first += count;
    _items[item].second = price;
}

void Shop::shipment(const std::map<Item, std::pair<int, int>>& items)
{
    _items = items;
}