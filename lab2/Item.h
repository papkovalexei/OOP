#ifndef H_ITEM
#define H_ITEM

#include <string>
#include <iostream>

class Item
{
public:
    Item();
    Item(const std::string& name, const int uid);

    friend std::ostream& operator<<(std::ostream& os, const Item& item)
    {
        os << "( " << item._uid << " ) " << item._name;

        return os;
    }

    bool operator<(const Item& other) const;

private:
    int _uid;
    std::string _name;
};

#endif