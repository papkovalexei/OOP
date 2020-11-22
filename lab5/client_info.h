#ifndef H_CLIENT_INFO
#define H_CLIENT_INFO

#include <vector>
#include <map>

#include "card.h"

struct client_info
{
public:
    client_info() {}

    std::map<std::string, std::string> info;
};

#endif