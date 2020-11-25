#ifndef H_BANK
#define H_BANK

#include <map>
#include <memory>
#include <iostream>

#include "cbank_info.h"
#include "cclient.h"

class cbank
{
public:
    enum ERROR_BANK
    {
        NOT_EXIST_CLIENT,
        NOT_EXIST_PROGRAM
    };

    cbank(cbank_info info) 
    {
        _bank_info = info;
        _getter_program_id.assign(_bank_info.accounts.size(), 1);
    }
   
    void add_client(cclient& client)
    {
        _clients[client.get_id()] = client;

        if (client.get_info("passport").empty() || client.get_info("address").empty())
        {
            _clients[client.get_id()].set_status(true);
        }
        else
        {
            _clients[client.get_id()].set_status(false);
        }

    }

    template <class T>
    ccard create_account(int id_client, int id_program)
    {
        if (_clients.count(id_client) == 0)
            throw ERROR_BANK::NOT_EXIST_CLIENT;
        if (_bank_info.accounts.count(id_program) == 0)
            throw ERROR_BANK::NOT_EXIST_PROGRAM;

        ccard card{_bank_info.id_bank, id_program, _getter_program_id[id_program]++};
        
        T* account = new T(dynamic_cast<T*>(_bank_info.accounts[id_program]));
        account->set_card(card);
        _available_account[std::pair<int, int>(card._id_program, card._id_card)] = account;
        _clients[id_client].add_account(account);

        return card;
    }

    int get_id() const
    {
        return _bank_info.id_bank;
    }

    caccount* get_account(ccard card)
    {
        return _available_account[std::pair<int, int>(card.get_id_program(), card.get_id_card())];
    }

    friend std::ostream& operator<<(std::ostream& os, cbank& bank)
    {
        os << "├─┬ ID: " << bank._bank_info.id_bank << std::endl;
        os << "│ └──┬ Information:" << std::endl;
        
        for (auto it = bank._bank_info.accounts.begin(); it != bank._bank_info.accounts.end(); it++)
        {
            auto buff = (*it).second;

            if (dynamic_cast<cdeposit_account*>(buff))
            {
                os << "│    ├──┬ ID program: " << (*it).first << "  Name: " << *dynamic_cast<cdeposit_account*>(buff);
            }

            if (dynamic_cast<ccredit_account*>(buff))
            {
                os << "│    ├──┬ ID program: " << (*it).first << "  Name: " << *dynamic_cast<ccredit_account*>(buff);
            }

            if (dynamic_cast<cdebit_account*>(buff))
            {
                os << "│    ├──┬ ID program: " << (*it).first << "  Name: " << *dynamic_cast<cdebit_account*>(buff);
            }

            os << "│    │\n";
        }

        os << "│ └──┬ Clients:" << std::endl;

        for (auto it = bank._clients.begin(); it != bank._clients.end(); it++)
        {
            os << (*it).second;
            os << "│    │\n";
        }

        return os;
    }

private:
    cbank_info _bank_info;
    std::map<std::pair<int, int>, caccount*> _available_account;
    std::map<int, cclient> _clients;

    std::vector<int> _getter_program_id;
};

#endif