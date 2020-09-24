#include <set>
#include <cstdlib>

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
    if (shop_UID < 0 || item_UID < 0 || count <= 0 || price < 0)
        return 4;

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

int Ecosystem::getCheapShop(const int& item_UID) const
{
    if (item_UID < 0 || item_UID >= _items.size())
        return -1;
    if (_shops.size() == 0)
        return -2;

    int answer_UID = -1, min_price = -1;

    for (auto it = _shops.begin() + 1; it != _shops.end(); it++)
    {
        if ((*it).getPriceItem(item_UID) != -1)
        {
            if (min_price == -1)
            {
                answer_UID = (*it).getUID();
                min_price = (*it).getPriceItem(item_UID);
                continue;
            }

            if ((*it).getPriceItem(item_UID) < min_price)
            {
                min_price = (*it).getPriceItem(item_UID);
                answer_UID = (*it).getUID();
            }
        }
    }

    if (answer_UID == -1)
        return -3;

    return answer_UID;
}

int Ecosystem::showShop(const int& shop_UID) const
{
    if (shop_UID < 0 || shop_UID >= _shops.size())
        return -1;

    for (auto it = _shops.begin(); it != _shops.end(); it++)
    {
        if ((*it).getUID() == shop_UID)
        {
            std::cout << (*it) << std::endl;
            break;
        }
    }

    return 0;
}

int Ecosystem::whichItem(const int& shop_UID, const int& money) const
{
    if (shop_UID < 0 || shop_UID >= _shops.size())
        return -1;
    
    for (auto it = _shops.begin(); it != _shops.end(); it++)
    {
        if ((*it).getUID() == shop_UID)
        {
            auto items = (*it).getAllItems();

            for (auto iterat = items.begin(); iterat != items.end(); iterat++)
            {
                if ((*iterat).second.first == 0 || (*iterat).second.second > money)
                    iterat = items.erase(iterat);
                else
                {
                    int sum = 0, count = 0;

                    for (int i = 0; i < (*iterat).second.first; i++)
                    {
                        if (sum + (*iterat).second.second <= money)
                        {
                            count = i + 1;
                            sum += (*iterat).second.second;
                        }
                        else
                            break;
                    }

                    std::cout << "buy: " << (*iterat).first << "  count: " << count << "  sum: " << sum << std::endl;
                }
            }
        }
    }
    return 0;
}