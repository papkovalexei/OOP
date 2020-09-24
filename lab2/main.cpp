#include "Ecosystem.h"

int main()
{
    Ecosystem system;

    system.createShop("Chip-Dip", "Dekabristov 14");
    system.createShop("Pyatorochka", "Nevsrie 8k1");
    system.createShop("Diksi", "Sennaya 8k1");

    system.createItem("Floor");
    system.createItem("CPU");
    system.createItem("GP");
    system.createItem("Milk");

    system.shipment(0, 2, 10, 3);
    system.shipment(0, 1, 10, 2);
    system.shipment(0, 3, 10, 1);

   // system.showSystem();
    system.showShop(0);
    system.whichItem(0, 12);

    return 0;
}