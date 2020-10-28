#include <iostream>

#include "RaceAir.h"

#include "Broom.h"
#include "Stupa.h"
#include "MagicCarpet.h"

#include "BactrianCamel.h"
#include "SpeedCamel.h"
#include "Centaur.h"
#include "SpeedBoots.h"

int main()
{
    Race race(100.0);

    Broom broom;
    SpeedCamel speedcamel;
    Stupa stupa;
    MagicCarpet magic;

    race.addTransport(&broom);
    race.addTransport(&stupa);
    race.addTransport(&magic);
    race.addTransport(&speedcamel);

    std::cout << (*race.run()[0]).getName() << std::endl;

    return 0;
}