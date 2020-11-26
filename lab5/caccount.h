#ifndef H_ACCOUNT
#define H_ACCOUNT

#include <vector>
#include <iostream>

#include "ccard.h"

class caccount
{
public:
    enum ERROR_ACCOUNT
    {
        ENOUGH_MONEY,
        NOT_YET
    };

    virtual ~caccount() {}
    virtual void withdraw_money(float money) = 0;
    virtual void put_money(float money) = 0;
    virtual void transfer_money(float money, caccount* to) = 0; 
    virtual void recalculation() = 0;

    void set_card(ccard card)
    {
        _card = card;
    }

    ccard get_card()
    {
        return _card;
    }

    friend std::ostream& operator<<(std::ostream& os, caccount* account)
    {
        os << "Money: " << account->_money << " " << account->_card;
        return os;
    }
protected:
    float _money = 0;
    ccard _card;
};

class ccredit_account : public caccount
{
public:
    ccredit_account(caccount* account)
    {
        this->_comission = dynamic_cast<ccredit_account*>(account)->_comission;
        this->_limit = dynamic_cast<ccredit_account*>(account)->_limit;
        this->_money = dynamic_cast<ccredit_account*>(account)->_money;
    }

    ccredit_account(float comission, float limit)
        : _comission(comission), _limit(limit)
    {
        _money = 0;
    }

    void recalculation() override
    {

    }

    void withdraw_money(float money) override
    {
        float to_bank = 0;
        if (_money - money < 0)
        {
            to_bank += (money * _comission / 100.0);
            money *= (1 + _comission / 100.0);
        }

        if (_money - money > _limit)
            _money -= money;
        else
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        float to_bank = 0;
        if (_money - money < 0)
        {
            to_bank += (money * _comission / 100.0);
            money *= (1 + _comission / 100.0);
        }

        if (_money - money > _limit)
        {
            to->put_money(money - to_bank);
            _money -= money;
        }
        else
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
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
        this->_delta = dynamic_cast<cdebit_account*>(account)->_delta;
        this->_time = dynamic_cast<cdebit_account*>(account)->_time;
        this->_money = dynamic_cast<cdebit_account*>(account)->_money;
        this->_percent = dynamic_cast<cdebit_account*>(account)->_percent;
    }

    cdebit_account(float percent)
        : _percent(percent), _time(0), _delta(0)
    {
        _money = 0;
    }

    void recalculation()
    {
        _time++;
        _delta += (_money * (_percent / 100.0 / 365.0));

        if (_time == 3)
        {
            _money += _delta;
            _delta = 0;
            _time = 0;
        }
    }

    void withdraw_money(float money) override
    {
        if (_money - money < 0)
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
        _money -= money;
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        if (_money - money < 0)
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
        to->put_money(money);
        _money -= money;
    }

    friend std::ostream& operator<<(std::ostream& os, cdebit_account account)
    {
        os << "Debit" << std::endl;
        os << "│    │  └── Percent: " << account._percent << "%" << std::endl;

        return os;
    }
private:
    float _percent;
    int _time;
    float _delta;
};

class cdeposit_account : public caccount
{
public:
    cdeposit_account(caccount* account)
    {
        this->_time = dynamic_cast<cdeposit_account*>(account)->_time;
        this->_delta = dynamic_cast<cdeposit_account*>(account)->_delta;
        this->_period = dynamic_cast<cdeposit_account*>(account)->_period;
        this->_money = dynamic_cast<cdeposit_account*>(account)->_money;
        this->_intervals = dynamic_cast<cdeposit_account*>(account)->_intervals;
    }

    cdeposit_account(const std::vector<std::pair<std::pair<float, float>, float>>& intervals, int period)
        : _intervals(intervals), _time(0), _delta(0), _period(period)
    {
        _money = 0;
    }

    void withdraw_money(float money) override
    {
        if (_period != 0)
            throw ERROR_ACCOUNT::NOT_YET;
        if (_money - money < 0)
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
        _money -= money;
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        if (_period != 0)
            throw ERROR_ACCOUNT::NOT_YET;
        if (_money - money < 0)
            throw ERROR_ACCOUNT::ENOUGH_MONEY;
        to->put_money(money);
        _money -= money;
    }

    void recalculation() override
    {
        _time++;

        for (auto it = _intervals.begin(); it != _intervals.end(); it++)
        {
            if (_money > (*it).first.first && _money < (*it).first.second)
            {
                _delta += (_money * (*it).second / 100.0 / 365.0);
                break;
            }
        }

        if (_time == _period)
        {
            _money += _delta;
            _delta = 0;
            _time = 0;
        }
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
    int _delta;
    int _time;
    int _period;
    std::vector<std::pair<std::pair<float, float>, float>> _intervals;
};

#endif