#ifndef H_CLIENT_BUILDER
#define H_CLIENT_BUILDER

#include <string>

#include "cclient.h"

class cclient_builder
{
public:
    virtual ~cclient_builder() {}
    virtual void create_id() = 0;
    virtual void set_name_surname(const std::string& name, const std::string& surname) = 0;
    virtual void set_passport(const std::string& passport) = 0;
    virtual void set_address(const std::string& address) = 0;
};

class cconcrete_client_builder : public cclient_builder
{
public:
    cconcrete_client_builder()
    {
        this->reset();
    }

    void reset()
    {
        _client = new cclient();
    }

    void create_id() override
    {
        _client->set_id(_id_client++);
    }

    void set_name_surname(const std::string& name, const std::string& surname) override
    {
        _client->set_info("name", name);
        _client->set_info("surname", surname);
    }

    void set_address(const std::string& address) override
    {
        _client->set_info("address", address);
    }

    void set_passport(const std::string& passport) override
    {
        _client->set_info("passport", passport);
    }

    cclient get_client()
    {
        cclient result = *_client;
        reset();
        return result;
    }

private:
    cclient* _client;
    static int _id_client;
};

int cconcrete_client_builder::_id_client = 0;

#endif