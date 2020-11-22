#include <iostream>
#include <vector>
#include <fstream>

#include "card.h"
#include "system_bank.h"

int main()
{
    std::ofstream log("stat.log");
    std::vector<bank> banks;

    director_bank* director = new director_bank();
    concrete_bank_builder* build = new concrete_bank_builder();

    director->set_builder(build);
    
    for (int i = 0; i < 10; i++)
    {
        director->random_build();
        banks.push_back(build->get_bank());

        log << banks[banks.size() - 1] << std::endl << "--------------------------------------\n";
    }

    log.close();

    return 0;
}