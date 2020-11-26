#ifndef H_BANK_BUILDER
#define H_BANK_BUILDER

#include "cbank.h"

class cbank_builder
{
public:
    virtual ~cbank_builder() {}
    virtual void create_bank_id() = 0;
    virtual void create_warning_limit(float limit, int time) = 0;
    virtual void create_account(caccount* account) = 0;
};

class cconcrete_bank_builder : public cbank_builder
{
public:
    cconcrete_bank_builder()
    {
        this->reset();
    }

    void reset()
    {
        bank = new cbank_info();
        id_program = 0;
    }

    void create_bank_id() override
    {
        bank->id_bank = id_bank++;
    }

    void create_warning_limit(float limit, int time) override
    {
        bank->warning_limit = limit;
        bank->time_limit = time;
    }

    void create_account(caccount* account) override
    {
        bank->accounts[id_program++] = account;
    }

    cbank* get_bank()
    {
        cbank* result = new cbank{*bank};

        this->reset();
        return result;
    }

private:
    cbank_info* bank;
    static int id_bank;
    int id_program;
};

int cconcrete_bank_builder::id_bank = 0;

class director_bank 
{
public:
    void set_builder(cbank_builder* builder)
    {
        this->builder = builder;
    }

    void standard_bank()
    {
        ccredit_account* credit = new ccredit_account{10, -20'000};
        cdebit_account* debit = new cdebit_account{4};

        std::vector<std::pair<std::pair<float, float>, float>> buffer_intervals;
        std::pair<std::pair<float, float>, float> buffer_pair;

        buffer_pair.first.first = 0;
        buffer_pair.first.second = 50'000;
        buffer_pair.second = 3;
        buffer_intervals.push_back(buffer_pair);

        buffer_pair.first.first = 50'000;
        buffer_pair.first.second = 100'000;
        buffer_pair.second = 3.5;
        buffer_intervals.push_back(buffer_pair);

        buffer_pair.first.first = 100'000;
        buffer_pair.first.second = __FLT_MAX__;
        buffer_pair.second = 4;
        buffer_intervals.push_back(buffer_pair);

        cdeposit_account* deposit = new cdeposit_account{buffer_intervals, 4};

        builder->create_bank_id();
        builder->create_warning_limit(10'000, 10);
        builder->create_account(credit);
        builder->create_account(debit);
        builder->create_account(deposit);
    }

    void random_bank()
    {
        ccredit_account* credit = new ccredit_account{std::rand() % 20 + 1, std::rand() % 100'000 * (-1)};
        cdebit_account* debit = new cdebit_account{std::rand() % 10 + 1};

        int left = 0, right = std::rand() % 100'000;
        std::vector<std::pair<std::pair<float, float>, float>> buffer_intervals;
        std::pair<std::pair<float, float>, float> buffer_pair;


        for (int i = 0; i < 3; i++)
        {
            buffer_pair.first.first = left;
            buffer_pair.first.second = right;
            buffer_pair.second = std::rand() % 10 + 1;
            buffer_intervals.push_back(buffer_pair);

            left = right;
            right += std::rand() % 50'000;
        }

        cdeposit_account* deposit = new cdeposit_account{buffer_intervals, rand() % 30};

        builder->create_bank_id();
        builder->create_warning_limit(std::rand() % 100'000, rand() % 30 + 1);
        builder->create_account(credit);
        builder->create_account(debit);
        builder->create_account(deposit);
    }
private:
    cbank_builder* builder;
};


#endif