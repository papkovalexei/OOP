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

    void load(const std::string& path);

    int getInteger(std::string section, std::string variable) const;
    float getFloat(std::string section, std::string variable) const;
    std::string getString(std::string section, std::string variable) const;

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