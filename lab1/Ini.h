#include <iostream>
#include <exception>
#include <vector>
#include <fstream>

#include "Section.h"

class Ini 
{
public:
    Ini();
    Ini(const std::string& path);

    void show() const;

    enum Error
    {
        GOOD,
        INCORRECT_FORMAT,
        FILE_NOT_EXISTS
    };
private:

    Error parse(const std::string& path);

    std::vector<Section> _data;
};