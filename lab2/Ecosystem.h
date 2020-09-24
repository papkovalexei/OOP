#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <iostream>
#include <vector>

#include "Shop.h"
#include "Item.h"

class Ecosystem
{
public:
    Ecosystem();

    int createShop(const std::string& name, const std::string& address);
    int createItem(const std::string& name);

    int getCheapShop(const int& item_UID) const;

    int shipment(const int& shop_UID, const int& item_UID, const int& count, const int& price);

    void showSystem() const;
    int showShop(const int& shop_UID) const;

    int whichItem(const int& shop_UID, const int& money) const;
private:
    std::vector<Shop> _shops;
    std::vector<Item> _items;

    int _next_uid_shop;
    int _next_uid_item;
};

#endif