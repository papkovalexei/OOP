#ifndef H_BANK_INFO
#define h_BANK_INFO

#include <vector>
#include <iostream>

struct bank_info
{
    bank_info()
        : debit_percent(-1), credit_comission_percent(-1), credit_limit(-1), warning_limit(-1)
    {}

    int bank_id;
    float debit_percent;
    float credit_comission_percent;
    float credit_limit;
    float warning_limit;
    std::vector<std::pair<std::pair<float, float>, float>> deposit;
};

#endif