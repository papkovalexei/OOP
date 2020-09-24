#include <map>

#include "Ecosystem.h"

int main()
{
    std::map<std::string, int> shops;
    std::map<std::string, int> items;

    Ecosystem system;

    shops["Chip-Dip"]    = system.createShop("Chip-Dip", "Dekabristov 14");
    shops["Pyatorochka"] = system.createShop("Pyatorochka", "Nevsrie 8k1");
    shops["Diksi"]       = system.createShop("Diksi", "Sennaya 8k1");

    items["Floor"] = system.createItem("Floor");
    items["CPU"]   = system.createItem("CPU");
    items["GP"]    = system.createItem("GP");
    items["Milk"]  = system.createItem("Milk");

    system.shipment(shops["Chip-Dip"], items["GP"], 10, 3);
    system.shipment(shops["Chip-Dip"], items["CPU"], 10, 2);
    system.shipment(shops["Chip-Dip"], items["Milk"], 9, 4);

    std::cout << system.sumShipment(shops["Chip-Dip"], items["Milk"], 7) << std::endl;

    return 0;
}