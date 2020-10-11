#include <map>
#include <ctime>

#include "Ecosystem.h"

int main()
{
    std::srand(std::time(0));

    std::map<std::string, int> shops;
    std::map<std::string, int> items;

    Ecosystem system;

    shops["Chip-Dip"]    = system.createShop("Chip-Dip", "Dekabristov 14");
    shops["Pyatorochka"] = system.createShop("Pyatorochka", "Nevsrie 8k1");
    shops["Diksi"]       = system.createShop("Diksi", "Sennaya 8k1");

    items["Floor"]  = system.createItem("Floor");
    items["CPU"]    = system.createItem("CPU");
    items["GP"]     = system.createItem("GP");
    items["Milk"]   = system.createItem("Milk");
    items["Bread"]  = system.createItem("Bread");
    items["Pocket"] = system.createItem("Pocket");
    items["Pen"]    = system.createItem("Pen");
    items["Paper"]  = system.createItem("Paper");
    items["Al"]     = system.createItem("Al");
    items["Card"]   = system.createItem("Card"); 


    for (auto shop = shops.begin(); shop != shops.end(); shop++)
        for (auto item = items.begin(); item != items.end(); item++)
            system.shipment((*shop).second, (*item).second, rand() % 30 + 10, rand() % 100 + 10);
    
    system.showShop(shops["Diksi"]);

    std::vector<std::pair<int, int>> buy;

    buy.push_back(std::pair<int, int>(items["CPU"], 4));
    buy.push_back(std::pair<int, int>(items["GP"], 7));
    buy.push_back(std::pair<int, int>(items["Al"], 2));

    std::cout << "Sum: " << system.buyItems(shops["Diksi"], buy) << std::endl;

    system.showShop(shops["Diksi"]);

    //system.showShop(system.getCheapShop(items["CPU"]));
    //system.countBuyItems(shops["Diksi"], 200);

    return 0;
}