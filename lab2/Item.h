#ifndef ITEM_H
#define ITEM_H

#include <iostream>

class Item
{
public:
    Item();
    Item(const std::string& name, const int& uid);

    int getUID() const;

    friend std::ostream& operator<<(std::ostream& os, const Item& item)
    {
        os << item._name << " (" << item._uid << ")"; 
        return os;
    }
private:
    int _uid;
    std::string _name;
};

#endif