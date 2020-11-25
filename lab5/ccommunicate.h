#ifndef H_COMMUNICATE
#define H_COMMUNICATE

#include "cbank.h"
#include "ccard.h"

class ccommand
{
public:
    virtual ~ccommand() {}
    virtual void execute() = 0;
protected:
    ccommand(std::vector<cbank*>& bank)
        : _bank(bank)
    {}

    std::vector<cbank*>& _bank;
};

class ctransfer_command : public ccommand
{
public:
    ctransfer_command(std::vector<cbank*>& bank, ccard from, ccard to, float money)
        : ccommand(bank), _from(from), _to(to), _money(money)
    {}

    void execute() override
    {
        
    }
private:
    ccard _from, _to;
    float _money;
};

#endif