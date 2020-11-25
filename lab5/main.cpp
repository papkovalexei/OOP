#include <iostream>
#include <vector>
#include <fstream>

#include "cbank.h"
#include "cbank_builder.h"
#include "cclient_builder.h"

struct chuman
{
    chuman() {}
    std::string name, surname, address;
};

void init(std::map<int, cbank*>& bank, std::vector<ccard>& accounts)
{
    std::vector<chuman> names;
    std::ifstream name_file("name");

    while (!name_file.eof())
    {
        chuman buffer;

        name_file >> buffer.name;
        name_file >> buffer.surname;
        name_file >> buffer.address;
        
        names.push_back(buffer);
    }

    std::ofstream log("log");

    cconcrete_client_builder* builder_client = new cconcrete_client_builder();

    cconcrete_bank_builder* builder = new cconcrete_bank_builder();
    director_bank* director = new director_bank();

    director->set_builder(builder);

    for (int i = 0; i < 3; i++)
    {
        director->random_bank();

        auto buffer = builder->get_bank();

        bank[buffer->get_id()] = buffer;
    }

    for (int i = 0; i < names.size(); i++)
    {
        builder_client->create_id();
        builder_client->set_address(names[i].address);
        builder_client->set_name_surname(names[i].name, names[i].surname);
        builder_client->set_passport(std::to_string(std::rand() % 100'000'0 + 100));

        int buffer = rand() % 3;
        auto client = builder_client->get_client();

        bank[buffer]->add_client(client);
        accounts.push_back(bank[buffer]->create_account<ccredit_account>(client.get_id(), 0));
    }

    for (int i =  0; i < 3; i++)
        log << *bank[i] << std::endl;
}

int main()
{
    std::map<int, cbank*> bank;
    std::vector<ccard> accounts;

    init(bank, accounts);

    return 0;
}