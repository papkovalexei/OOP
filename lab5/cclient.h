#ifndef H_CLIENT
#define H_CLIENT

#include <string>
#include <iostream>
#include <map>
#include <vector>

#include "caccount.h"
#include "ccard.h"

class cclient
{
public:
    cclient() 
        : _status(true)
    {}

    void set_id(int id)
    {
        _id_client = id;
    }

    int get_id() const
    {
        return _id_client;
    }

    void set_info(const std::string& first, const std::string& second)
    {
        _information[first] = second;
    }

    void add_account(caccount* account)
    {
        _accounts.push_back(account);
    }

    friend std::ostream& operator<<(std::ostream& os, cclient& client)
    {
        if (client._status)
            os << "│    ├──┬ ID client(+): " << client._id_client << std::endl;
        else
            os << "│    ├──┬ ID client(-): " << client._id_client << std::endl;
        os << "│    │  ├── Name " << client._information["name"] << " " << client._information["surname"] << std::endl;

        if (client._information.count("passport") != 0)
            os << "│    │  ├── Passport: " << client._information["passport"] << std::endl;

        if (client._information.count("address") != 0)
            os << "│    │  ├── Address: " << client._information["address"] << std::endl;

        os << "│    │  │\n│    │  └─┬ Account: " << std::endl;

        for (auto it = client._accounts.begin(); it != client._accounts.end(); it++)
        {
            os << "│    │    ├─ " << (*it);
        }

        return os;
    }

    std::string get_info(const std::string& field)
    {
        return _information[field];
    }

    void set_limits(float money_limit, int time_limit)
    {
        _status = false;
        for (int i = 0; i < _accounts.size(); i++)
        {
            _accounts[i]->set_limits(money_limit, time_limit);
        }
    }

    void delete_limits()
    {
        for (int i = 0; i < _accounts.size(); i++)
            _accounts[i]->delete_limits();
    }

    void recalculation()
    {
        for (int i = 0; i < _accounts.size(); i++)
        {
            _accounts[i]->recalculation();
        }
    }

private:
    int _id_client;
    bool _status;
    std::map<std::string, std::string> _information; // "passport" = "2817318298ABD22" "name" = "21312312"
    std::vector<caccount*> _accounts;
};

#endif