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

    system.shipment(1, 3, 10, 110);
    system.shipment(1, 3, 2, 228);
    system.shipment(1, 2, 1488, 20);
    system.shipment(1, 2, 10, 20);

    system.showSystem();

    return 0;
}