#ifndef H_ACCOUNT
#define H_ACCOUNT

#include <vector>
#include <iostream>

#include "ccard.h"

class caccount
{
public:
    virtual ~caccount() {}
    virtual void withdraw_money() = 0;
    virtual void put_money() = 0;
    virtual void transfer_money() = 0; 

    void set_card(ccard card)
    {
        _card = card;
    }

    ccard get_card()
    {
        return _card;
    }
private:
    ccard _card;
};

class ccredit_account : public caccount
{
public:
    ccredit_account(caccount* account)
    {
        this->_comission = dynamic_cast<ccredit_account*>(account)->_comission;
        this->_limit = dynamic_cast<ccredit_account*>(account)->_limit;
    }

    ccredit_account(float comission, float limit)
        : _comission(comission), _limit(limit)
    {}

    void withdraw_money() override
    {

    }

    void put_money() override
    {

    }

    void transfer_money() override
    {

    }

    friend std::ostream& operator<<(std::ostream& os, ccredit_account account)
    {
        os << "Credit" << std::endl;
        os << "│    │  └── Comission: " << account._comission << "%  limit: " << account._limit << std::endl;

        return os;
    }
private:
    float _comission;
    float _limit;
};

class cdebit_account : public caccount
{
public:
    cdebit_account(caccount* account)
    {
        this->_percent = dynamic_cast<cdebit_account*>(account)->_percent;
    }

    cdebit_account(float percent)
        : _percent(percent)
    {}

    void withdraw_money() override
    {

    }

    void put_money() override
    {

    }

    void transfer_money() override
    {

    }

    friend std::ostream& operator<<(std::ostream& os, cdebit_account account)
    {
        os << "Debit" << std::endl;
        os << "│    │  └── Percent: " << account._percent << "%" << std::endl;

        return os;
    }
private:
    float _percent;
};

class cdeposit_account : public caccount
{
public:
    cdeposit_account(caccount* account)
    {
        this->_intervals = dynamic_cast<cdeposit_account*>(account)->_intervals;
    }

    cdeposit_account(const std::vector<std::pair<std::pair<float, float>, float>>& intervals)
        : _intervals(intervals)
    {}

    void withdraw_money() override
    {

    }

    void put_money() override
    {

    }

    void transfer_money() override
    {

    }

    friend std::ostream& operator<<(std::ostream& os, cdeposit_account account)
    {
        os << "Deposit" << std::endl;

        for (auto it = account._intervals.begin(); it != account._intervals.end(); it++)
        {
            os << "│    │  ├── " << (*it).first.first << "-" << (*it).first.second << " : " << (*it).second << "%" << std::endl;
        }

        return os;
    }
private:
    std::vector<std::pair<std::pair<float, float>, float>> _intervals;
};

#endif