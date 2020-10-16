#include "Ecosystem.h"

Ecosystem::Ecosystem()
{

}

Ecosystem::Ecosystem(Ecosystem& system)
    : _shops(system._shops), _items(system._items)
{

}

int Ecosystem::createShop(const std::string& name, const std::string& address)
{
    _shops.push_back(Shop(name, address, _shops.size()));

    return _shops.size() - 1;
}

int Ecosystem::createItem(const std::string& name)
{
    _items.push_back(Item(name, _items.size()));

    return _items.size() - 1;
}

int Ecosystem::getCheapShop(const int item_UID) const
{
    try
    {
        checkValidArguments(item_UID, false);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    if (item_UID < 0 || item_UID >= _items.size())
        throw Error::INCORRECT_ITEM_UID;

    int answer_uid = -1, min_price = -1;

    for (auto& shop : _shops)
    {
        int now_uid = shop.getUID();
        int now_price = shop.getPriceItem(_items[item_UID]);

        if (min_price == -1 && now_price != -1)
        {
            min_price = now_price;
            answer_uid = now_uid;
            continue;
        }

        if (now_price < min_price)
        {
            min_price = now_price;
            answer_uid = now_uid;
        }
    }

    if (answer_uid == -1)
        throw Error::ALL_SHOP_EMPTY;

    return answer_uid;
}

void Ecosystem::shipment(const int shop_UID, const int item_UID, const int count, const int price)
{
    try
    {
        checkValidArguments(shop_UID, item_UID, count, price);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    _shops[shop_UID].shipment(_items[item_UID], count, price);
}

void Ecosystem::shipment(const int shop_UID, const int item_UID, const int count)
{
    try
    {
        checkValidArguments(shop_UID, item_UID, count);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    _shops[shop_UID].shipment(_items[item_UID], count);
}

void Ecosystem::showSystem() const
{
    for (auto& item : _items)
        std::cout << item << std::endl;
    std::cout << "----------------------------------" << std::endl;

    for (auto& shop : _shops)
        std::cout << shop << std::endl;
}

void Ecosystem::showShop(const int shop_UID) const
{
    try
    {
        checkValidArguments(shop_UID, true);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    std::cout << _shops[shop_UID] << std::endl;
}

void Ecosystem::countBuyItems(const int shop_UID, const int money) const
{
    try
    {
        checkValidArguments(shop_UID, money);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    for (auto& item : _shops[shop_UID].getAllItem())
    {
        int count = 0, count_item = item.second.first;
        int cash = money;

        while (cash - item.second.second > 0 && count_item > 0)
        {
            count_item--;
            count++;
            cash -= item.second.second;
        }

        if (count > 0)
            std::cout << item.first << " count: " << count << " for the sum " << money - cash << std::endl;
    }
}

int Ecosystem::buyItems(const int shop_UID, const std::vector<std::pair<int, int>>& items)
{
    try
    {
        checkValidArguments(shop_UID, true);
    }
    catch(const Error ex)
    {
        throw ex;
    }

    if (items.empty())
        throw Error::INCORRECT_SHIP;

    auto item_in_shop = _shops[shop_UID].getAllItem();

    int answer = 0;

    for (auto& now_item : items)
    {
        if (now_item.first <= 0 || now_item.second <= 0)
            throw Error::INCORRECT_SHIP;

        if (item_in_shop.count(_items[now_item.first]) == 0)
            return -1;

        if (item_in_shop[_items[now_item.first]].first < now_item.second)
            return -1;
        
        item_in_shop[_items[now_item.first]].first -= now_item.second;
        answer += now_item.second * item_in_shop[_items[now_item.first]].second;
    }

    _shops[shop_UID].shipment(item_in_shop);

    return answer;
}

void Ecosystem::checkValidArguments(const int shop_UID, const int item_UID, const int count, const int price) const
{
    checkValidArguments(shop_UID, item_UID, count);

    if (price <= 0)
        throw Error::INCORRECT_PRICE;
}

void Ecosystem::checkValidArguments(const int shop_UID, const int item_UID, const int count) const
{
    checkValidArguments(shop_UID, true);
    checkValidArguments(item_UID, false);

    if (count <= 0)
        throw Error::INCORRECT_COUNT;
}

void Ecosystem::checkValidArguments(const int shop_UID, const int money) const
{
    checkValidArguments(shop_UID, true);

    if (money <= 0)
        throw Error::INCORRECT_MONEY;
}

void Ecosystem::checkValidArguments(const int uid, bool flag) const
{
    if (flag)
    {
        if (uid < 0 || uid >= _shops.size())
            throw Error::INCORRECT_SHOP_UID;
    }
    else
    {
        if (uid < 0 || uid >= _items.size())
            throw Error::INCORRECT_ITEM_UID;
    }
}