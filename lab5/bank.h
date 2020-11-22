#ifndef H_BANK
#define H_BANK

#include <vector>

#include "bank_info.h"
#include "client_info.h"

class bank
{
public:
    bank(bank_info info)
        : _bank_info(info)
    {}

    void set_bank_info(const bank_info& info)
    {
        _bank_info = info;
    }

    bank_info get_bank_info() const
    {
        return _bank_info;
    }

    void print() const
    {
        std::cout << "ID: " << _bank_info.bank_id << std::endl;
        std::cout << "Debit percent: " << _bank_info.debit_percent << std::endl;
        std::cout << "Credit: limit(" << _bank_info.credit_limit << ")  percent(" << _bank_info.credit_comission_percent << ")" << std::endl;
        std::cout << "Deposit: " << std::endl;

        for (auto it = _bank_info.deposit.begin(); it != _bank_info.deposit.end(); it++)
            std::cout << (*it).first.first << " - " << (*it).first.second << " = " << (*it).second << std::endl;
        std::cout << "Warning limit: " << _bank_info.warning_limit << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const bank& _bank)
    {
        os << "ID: " << _bank._bank_info.bank_id << std::endl;
        os << "Debit percent: " << _bank._bank_info.debit_percent << std::endl;
        os << "Credit: limit(" << _bank._bank_info.credit_limit << ")  percent(" << _bank._bank_info.credit_comission_percent << ")" << std::endl;
        os << "Deposit: " << std::endl;

        for (auto it = _bank._bank_info.deposit.begin(); it != _bank._bank_info.deposit.end(); it++)
            os << (*it).first.first << " - " << (*it).first.second << " = " << (*it).second << std::endl;
        os << "Warning limit: " << _bank._bank_info.warning_limit << std::endl;

        return os;
    }
private:
    bank_info _bank_info;
    std::vector<client_info> _client;
    std::vector<card> _cards;
};

#endif