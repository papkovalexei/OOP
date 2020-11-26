#ifndef H_BANK_INFO
#define H_BANK_INFO

#include <map>
#include <memory>

#include "caccount.h"

struct cbank_info
{
public:
    cbank_info() {}

    std::map<int, caccount*> accounts;
    float warning_limit;
    int time_limit;
    int id_bank;
};

#endif