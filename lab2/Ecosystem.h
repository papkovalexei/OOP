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
    void shipment(const int shop_UID, const int item_UID, const int count);

    void countBuyItems(const int shop_UID, const int money) const;
    int buyItems(const int shop_UID, const std::vector<std::pair<int, int>>& items);

    void showSystem() const;
    void showShop(const int shop_UID) const;

    enum Error
    {
        INCORRECT_SHOP_UID,
        INCORRECT_ITEM_UID,
        INCORRECT_COUNT,
        INCORRECT_PRICE,
        INCORRECT_MONEY,
        INCORRECT_SHIP,
        ALL_SHOP_EMPTY
    };

private:
    void checkValidArguments(const int shop_UID, const int item_UID, const int count, const int price) const;
    void checkValidArguments(const int shop_UID, const int item_UID, const int count) const;
    void checkValidArguments(const int shop_UID, const int money) const;
    void checkValidArguments(const int UID, bool flag) const; // flag = true (shop), false (item)

    std::vector<Shop> _shops;
    std::vector<Item> _items;
};

#endif