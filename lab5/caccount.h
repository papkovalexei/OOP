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
        NOT_YET,
        LIMIT
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

    void set_limits(float limit, int time_limit)
    {
        _limit_warning = limit;
        _time_limit = time_limit;
    }

    friend std::ostream& operator<<(std::ostream& os, caccount* account)
    {
        os << "Money: " << account->_money << " " << account->_card;
        return os;
    }
protected:
    bool check_valid_transaction(float money)
    {
        if (_limit_warning != -1)
        {
            if (_buffer_money + money > _limit_warning)
                return false;
            else
                return true;
        }

        return true;
    }

    float _limit_warning = -1;
    float _buffer_money = 0;
    int _time_limit = -1;
    int _time;

    float _money = 0;
    ccard _card;
};

class ccredit_account : public caccount
{
public:
    ccredit_account(caccount* account)
    {
        this->_time_limit = dynamic_cast<ccredit_account*>(account)->_time_limit;
        this->_limit_warning = dynamic_cast<ccredit_account*>(account)->_limit_warning;
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
        _time++;

        if (_limit_warning != -1)
        {
            if (_time % _time_limit)
                _buffer_money = 0;
        }
    }

    void withdraw_money(float money) override
    {
        if (check_valid_transaction(money))
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
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        if (check_valid_transaction(money))
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
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
        
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
        this->_time_limit = dynamic_cast<cdebit_account*>(account)->_time_limit;
        this->_limit_warning = dynamic_cast<cdebit_account*>(account)->_limit_warning;
        this->_delta = dynamic_cast<cdebit_account*>(account)->_delta;
        this->_time = dynamic_cast<cdebit_account*>(account)->_time;
        this->_money = dynamic_cast<cdebit_account*>(account)->_money;
        this->_percent = dynamic_cast<cdebit_account*>(account)->_percent;
    }

    cdebit_account(float percent)
        : _percent(percent), _delta(0)
    {
        _time = 0;
        _money = 0;
    }

    void recalculation()
    {
        _time++;

        if (_limit_warning != -1)
        {
            if (_time % _time_limit)
                _buffer_money = 0;
        }

        _delta += (_money * (_percent / 100.0 / 365.0));

        if (_time % 3 == 0)
        {
            _money += _delta;
            _delta = 0;
        }
    }

    void withdraw_money(float money) override
    {
        if (check_valid_transaction(money))
        {
            if (_money - money < 0)
                throw ERROR_ACCOUNT::ENOUGH_MONEY;
            _money -= money;
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
        
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        if (check_valid_transaction(money))
        {
            if (_money - money < 0)
                throw ERROR_ACCOUNT::ENOUGH_MONEY;
            to->put_money(money);
            _money -= money;
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
    }

    friend std::ostream& operator<<(std::ostream& os, cdebit_account account)
    {
        os << "Debit" << std::endl;
        os << "│    │  └── Percent: " << account._percent << "%" << std::endl;

        return os;
    }
private:
    float _percent;
    float _delta;
};

class cdeposit_account : public caccount
{
public:
    cdeposit_account(caccount* account)
    {
        this->_time_limit = dynamic_cast<cdeposit_account*>(account)->_time_limit;
        this->_limit_warning = dynamic_cast<cdeposit_account*>(account)->_limit_warning;
        this->_time = dynamic_cast<cdeposit_account*>(account)->_time;
        this->_delta = dynamic_cast<cdeposit_account*>(account)->_delta;
        this->_period = dynamic_cast<cdeposit_account*>(account)->_period;
        this->_money = dynamic_cast<cdeposit_account*>(account)->_money;
        this->_intervals = dynamic_cast<cdeposit_account*>(account)->_intervals;
    }

    cdeposit_account(const std::vector<std::pair<std::pair<float, float>, float>>& intervals, int period)
        : _intervals(intervals), _delta(0), _period(period)
    {
        _time = 0;
        _money = 0;
    }

    void withdraw_money(float money) override
    {
        if (check_valid_transaction(money))
        {
            if (_period != 0)
                throw ERROR_ACCOUNT::NOT_YET;
            if (_money - money < 0)
                throw ERROR_ACCOUNT::ENOUGH_MONEY;
            _money -= money;
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
    }

    void put_money(float money) override
    {
        _money += money;
    }

    void transfer_money(float money, caccount* to) override
    {
        if (check_valid_transaction(money))
        {
            if (_period != 0)
                throw ERROR_ACCOUNT::NOT_YET;
            if (_money - money < 0)
                throw ERROR_ACCOUNT::ENOUGH_MONEY;
            to->put_money(money);
            _money -= money;
            _buffer_money += money;
        }
        else
            throw ERROR_ACCOUNT::LIMIT;
    }

    void recalculation() override
    {
        _time++;

        if (_limit_warning != -1)
        {
            if (_time % _time_limit)
                _buffer_money = 0;
        }

        for (auto it = _intervals.begin(); it != _intervals.end(); it++)
        {
            if (_money > (*it).first.first && _money < (*it).first.second)
            {
                _delta += (_money * (*it).second / 100.0 / 365.0);
                break;
            }
        }

        if (_time % _period == 0)
        {
            _money += _delta;
            _delta = 0;
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
    int _period;
    std::vector<std::pair<std::pair<float, float>, float>> _intervals;
};

#endif