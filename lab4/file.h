#ifndef H_FILE
#define H_FILE

#include <string>
#include <iostream>

struct file
{
    file() {}
    file(std::string name_, int size_)
        : name(name_), size(size_)
    {

    }

    bool operator==(const file& other)
    {
        if (name == other.name && size == other.size)
            return true;
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const file& file_)
    {
        os << "Name: " << file_.name << "  size: " << file_.size;

        return os;
    }

    std::string name;
    int size;
};

#endif