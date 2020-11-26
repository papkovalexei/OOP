#include <iostream>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <utility>

#include "cbank.h"
#include "cbank_builder.h"
#include "cclient_builder.h"

struct chuman
{
    chuman() {}
    std::string name, surname, address;
};

template<class Func, class ...Args>
void run(int msec, Func func, Args &&...args){
    auto endless = [=](Args &&...args){
        while(true){
            func(args...);
            std::this_thread::sleep_for(std::chrono::milliseconds(msec));
        }
    };
    
    std::thread thread(endless, args...);
    
    thread.detach();
}

void timer_func(std::map<int, cbank*> bank)
{
    static int i = 0;

    for (auto it = bank.begin(); it != bank.end(); it++)
    {
        (*it).second->recalculation();
    }
    std::cout << "Recalculate" << std::endl;
    std::ofstream log("log" + std::to_string(i++));
    for (int i =  0; i < 3; i++)
        log << *bank[i] << std::endl;
}

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
        if (rand() % 2)
            builder_client->set_passport(std::to_string(std::rand() % 100'000'0 + 100));

        int buffer = rand() % 3;
        auto client = builder_client->get_client();

        bank[buffer]->add_client(client);
        accounts.push_back(bank[buffer]->create_account<cdebit_account>(client.get_id(), 1));
    }
}

int main()
{
    std::map<int, cbank*> bank;
    std::vector<ccard> accounts;

    init(bank, accounts);

    for (int i = 0; i < accounts.size(); i++)
    {
        cbank::cput_command* put = new cbank::cput_command(bank, accounts[i], 100'000);

        put->execute();
    }

    cbank::ctransfer_command* transfer = new cbank::ctransfer_command(bank, accounts[0], accounts[1], 50'000);
    transfer->execute();

    cbank::cwithdrawl_command* withdrawl = new cbank::cwithdrawl_command(bank, accounts[0], 20'002);
    withdrawl->execute();

    run(5000, timer_func, std::move(bank));

    int x;
    std::cin >> x;

    return 0;
}