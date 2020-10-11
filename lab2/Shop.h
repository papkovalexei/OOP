#ifndef H_SHOP
#define H_SHOP

#include <map>
#include <iostream>

#include "Item.h"

class Shop
{
public:
    Shop();
    Shop(const std::string& name, const std::string& address, const int uid);

    int getPriceItem(const Item& item) const;
    int getUID() const;
    const std::map<Item, std::pair<int, int>>& getAllItem() const;

    void shipment(const Item& item, const int count, const int price);

    friend std::ostream& operator<<(std::ostream& os, const Shop& shop)
    {
        os << "( " << shop._uid << " ) " << shop._name << " : " << shop._address << std::endl << "=========================" << std::endl;

        for (auto& item : shop._items)
            os << item.first << ": count = " << item.second.first << "  price = " << item.second.second << std::endl;

        return os;
    }

private:
    std::map<Item, std::pair<int, int>> _items;
    std::string _name;
    std::string _address;
    int _uid;
};

#endif