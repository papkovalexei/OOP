#ifndef SHOP_H
#define SHOP_H

#include <iostream>
#include <vector>

#include "Item.h"

class Shop 
{
public:
    Shop();
    Shop(const std::string& name, const std::string& address, const int& uid);

    int getUID() const;
    std::pair<Item, std::pair<int, int>>& getItems(const int& item_UID);

    void addItem(const Item& item);
    void addItem(const Item& item, const int& count, const int& price);

    int getPriceItem(const int& item_UID) const;
    std::vector<std::pair<Item, std::pair<int, int>>> getAllItems() const;

    friend std::ostream& operator<<(std::ostream& os, const Shop& shop)
    {
        os << shop._name << " (" << shop._uid << ")" << std::endl;
        os << "Address: " << shop._address << std::endl;
        
        for (auto it = shop._items.begin(); it != shop._items.end(); it++)
            os << "***: " << (*it).first << "  price: " << (*it).second.second << "  count: " << (*it).second.first << std::endl;
        return os;
    }
private:
    int _uid;
    std::string _name;
    std::string _address;
    std::vector<std::pair<Item, std::pair<int, int>>> _items; // first - item; second.first; - count second.second - price
};

#endif