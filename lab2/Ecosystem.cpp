#include "Ecosystem.h"

Ecosystem::Ecosystem() 
    : _next_uid_item(0), _next_uid_shop(0)
{

}

int Ecosystem::createShop(const std::string& name, const std::string& address)
{
    _shops.push_back(Shop(name, address, _next_uid_shop));   

    return _next_uid_shop++;
}

int Ecosystem::createItem(const std::string& name)
{
    _items.push_back(Item(name, _next_uid_item));

    return _next_uid_item++;
}

int Ecosystem::shipment(const int& shop_UID, const int& item_UID, const int& count, const int& price)
{
    auto iterator_shop = _shops.end();
    auto iterator_item = _items.end();

    for (auto it = _shops.begin(); it != _shops.end(); it++)
    {
        if ((*it).getUID() == shop_UID)
        {
            iterator_shop = it;
            break;
        }
    }

    if (iterator_shop == _shops.end())
        return 1;

    for (auto it = _items.begin(); it != _items.end(); it++)
    {
        if ((*it).getUID() == item_UID)
        {
            iterator_item = it;
            break;
        }
    }

    if (iterator_item == _items.end())
        return 2;

    try 
    {
        auto& item = (*iterator_shop).getItems(item_UID);

        item.second.first += count;
        item.second.second = price;
    }
    catch (int ex)
    {
        (*iterator_shop).addItem((*iterator_item), count, price);
    }
    return 0;
}

void Ecosystem::showSystem() const
{
    for (auto it = _items.begin(); it != _items.end(); it++)
        std::cout << (*it) << std::endl;
    std::cout << "===========================" << std::endl;

    for (auto it = _shops.begin(); it != _shops.end(); it++)
    {
        std::cout << (*it) << "-------------------------" << std::endl;
    }
}