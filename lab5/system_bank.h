#ifndef H_BANK_SYSTEM
#define H_BANK_SYSTEM

#include <map>

#include "bank.h"

class builder_bank
{
public:
    virtual ~builder_bank() {}
    virtual void bank_id() = 0;
    virtual void deposit(const std::vector<std::pair<std::pair<float, float>, float>>& percent) = 0;
    virtual void credit(float limit, float percent) = 0;
    virtual void warning(float limit) = 0;
    virtual void debit(float percent) = 0;
};

class concrete_bank_builder : public builder_bank
{
public:
    concrete_bank_builder()
    {
        this->reset();
    }

    ~concrete_bank_builder()
    {
        delete _bank_info;
    }

    void reset()
    {
        _bank_info = new bank_info();
    }

    void bank_id() override
    {
        _bank_info->bank_id = _bank_id++;
    }

    void deposit(const std::vector<std::pair<std::pair<float, float>, float>>& percent) override
    {
        _bank_info->deposit = percent;
    }

    void credit(float limit, float percent) override
    {
        _bank_info->credit_comission_percent = percent;
        _bank_info->credit_limit = limit;
    }

    void warning(float limit) override
    {
        _bank_info->warning_limit = limit;
    }

    void debit(float percent) override
    {
        _bank_info->debit_percent = percent;
    }

    bank get_bank()
    {
        bank _bank(*_bank_info);
        this->reset();
        return _bank;
    }
private:
    bank_info* _bank_info;
    static int _bank_id;
};

int concrete_bank_builder::_bank_id = 1;

class director_bank
{
public:
    void set_builder(builder_bank* build)
    {
        _builder = build;
    }

    void random_build()
    {
        std::vector<std::pair<std::pair<float, float>, float>> percent;
        std::pair<std::pair<float, float>, float> buffer;

        int left = 0, right = std::rand() % 100'000;
        float per = std::rand() % 10 + 1;
        buffer.first.first = left;
        buffer.first.second = right;
        buffer.second = per;
        percent.push_back(buffer);

        for (int i = 0; i < 2; i++)
        {
            left = right;
            right = left + std::rand() % 100'000;
            per = std::rand() % 10 + 1;
            buffer.first.first = left;
            buffer.first.second = right;
            buffer.second = per;
            percent.push_back(buffer);
        }

        _builder->bank_id();
        _builder->credit(std::rand() % 100'000 * (-1), std::rand() % 20 + 1);
        _builder->debit(std::rand() % 10 + 1);
        _builder->deposit(percent);
        _builder->warning(std::rand() % 100'000);
    }

    void standard_build()
    {
        std::vector<std::pair<std::pair<float, float>, float>> percent;
        std::pair<std::pair<float, float>, float> buffer;

        buffer.first.first = 0;
        buffer.first.second = 50'000;
        buffer.second = 3;
        percent.push_back(buffer);

        buffer.first.first = 50'000;
        buffer.first.second = 100'000;
        buffer.second = 3.5;
        percent.push_back(buffer);

        buffer.first.first = 100'000;
        buffer.first.second = INT32_MAX;
        buffer.second = 4;
        percent.push_back(buffer);

        _builder->bank_id();
        _builder->credit(-10'000, 10);
        _builder->debit(3.65);
        _builder->deposit(percent);
        _builder->warning(20'000);
    }
private:
    builder_bank* _builder;
};

class builder_client
{
public:
    virtual ~builder_client() {}
    virtual void set_name(const std::string& name, const std::string& surname) = 0;
    virtual void set_address(const std::string& address) = 0;
    virtual void set_passport(int passport) = 0;
};

class concrete_builder_client : public builder_client
{
public:
    concrete_builder_client()
    {
        this->reset();
    }

    ~concrete_builder_client()
    {
        delete _client_info;
    }

    void reset()
    {
        _client_info = new client_info();
    }

    void set_name(const std::string& name, const std::string& surname) override
    {  
        _client_info->info["name"] = name;
        _client_info->info["surname"] = surname;
    }

    void set_address(const std::string& address) override
    {
        _client_info->info["address"] = address;
    }

    void set_passport(int passport) override
    {
        _client_info->info["passport"] = passport;
    }

    client_info get_info()
    {
        client_info result =  *_client_info;
        reset();
        return result;
    }
private:
    client_info* _client_info;
};

#endif