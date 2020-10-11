#ifndef H_ECOSYSTEM
#define H_ECOSYSTEM

#include <vector>
#include <string>
#include <iostream>

#include "Shop.h"
#include "Item.h"

class Ecosystem
{
public:
    Ecosystem();
    Ecosystem(Ecosystem& system);

    int getCheapShop(const int item_UID) const;

    int createShop(const std::string& name, const std::string& address);
    int createItem(const std::string& name);

    void shipment(const int shop_UID, const int item_UID, const int count, const int price);

    void countBuyItems(const int shop_UID, const int money) const;

    void showSystem() const;
    void showShop(const int shop_UID) const;

    enum Error
    {
        INCORRECT_SHOP_UID,
        INCORRECT_ITEM_UID,
        INCORRECT_COUNT,
        INCORRECT_PRICE,
        ALL_SHOP_EMPTY
    };

private:
    std::vector<Shop> _shops;
    std::vector<Item> _items;
};

#endif