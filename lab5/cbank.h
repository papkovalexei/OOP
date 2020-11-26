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
        _available_account[std::pair<int, int>(card.get_id_program(), card.get_id_card())] = account;
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

    class ccommand
    {
    public:
        virtual ~ccommand() {}
        virtual void execute() = 0;
        virtual void cancel() = 0;
        virtual std::string get_description() = 0;
    protected:
        ccommand(std::map<int, cbank*>& bank)
            : _bank(bank)
        {}

        std::map<int, cbank*>& _bank;
    };

    void recalculation()
    {
        for (auto it = _clients.begin(); it != _clients.end(); it++)
        {
            (*it).second.recalculation();
        }
    }

    class ctransfer_command : public ccommand
    {
    public:
        ctransfer_command(std::map<int, cbank*>& bank, ccard from, ccard to, float money)
            : ccommand(bank), _from(from), _to(to), _money(money)
        {}

        void execute() override
        {
            auto from_account = _bank[_from.get_id_bank()]->get_account(_from);
            auto to = _bank[_to.get_id_bank()]->get_account(_to);

            _bank[from_account->get_card().get_id_bank()]->push_history(dynamic_cast<ccommand*>(this));
            _bank[to->get_card().get_id_bank()]->push_history(dynamic_cast<ccommand*>(this));

            from_account->transfer_money(_money, to);
        }

        std::string get_description() override
        {
            std::string result = "transfer: ";
            result += _from.get_number();
            result += " -> ";
            result += _to.get_number();
            result += "  (money: ";
            result += std::to_string(_money);
            result += ")";

            return result;
        }

        void cancel() override
        {
            auto from_account = _bank[_from.get_id_bank()]->get_account(_from);
            auto to = _bank[_to.get_id_bank()]->get_account(_to);

            to->transfer_money(_money, from_account);
        }
    private:
        ccard _from, _to;
        float _money;
    };

    class cwithdrawl_command : public ccommand
    {
    public:
        cwithdrawl_command(std::map<int, cbank*>& bank, ccard from, float money)
            : ccommand(bank), _from(from), _money(money)
        {}

        void execute() override
        {
            auto from_account = _bank[_from.get_id_bank()]->get_account(_from);

            _bank[from_account->get_card().get_id_bank()]->push_history(dynamic_cast<ccommand*>(this));
            
            from_account->withdraw_money(_money);
        }

        std::string get_description() override
        {
            std::string result = "Withdrawl: ";
            result += _from.get_number();
            result += " (money: ";
            result += std::to_string(_money);
            result += ")";

            return result;
        }

        void cancel() override
        {
            auto from_account = _bank[_from.get_id_bank()]->get_account(_from);

            from_account->put_money(_money);
        }

    private:
        ccard _from;
        float _money;
    };

    class cput_command : public ccommand
    {
    public:
        cput_command(std::map<int, cbank*>& bank, ccard to, float money)
            : ccommand(bank), _to(to), _money(money)
        {}

        void execute() override
        {
            auto to_account = _bank[_to.get_id_bank()]->get_account(_to);

            _bank[to_account->get_card().get_id_bank()]->push_history(dynamic_cast<ccommand*>(this));

            to_account->put_money(_money);
        }

        std::string get_description() override
        {
            std::string result = "Put: ";
            result += _to.get_number();
            result += " (money: ";
            result += std::to_string(_money);
            result += ")";
            return result;
        }

        void cancel() override
        {
            auto to_account = _bank[_to.get_id_bank()]->get_account(_to);

            to_account->withdraw_money(_money);
        }
    private:
        ccard _to;
        float _money;
    };

    void push_history(ccommand* command)
    {
        _history.push_back(command);
    }

private:
    cbank_info _bank_info;
    std::map<std::pair<int, int>, caccount*> _available_account;
    std::map<int, cclient> _clients;

    std::vector<ccommand*> _history;
    std::vector<int> _getter_program_id;
};

#endif