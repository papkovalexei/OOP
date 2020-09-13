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

    int getInteger(const std::string& section, const std::string& variable) const;
    float getFloat(const std::string& section, const std::string& variable) const;
    std::string getString(const std::string& section, const std::string& variable) const;

    void show() const;

    enum ErrorParser
    {
        GOOD,
        INCORRECT_FORMAT,
        FILE_NOT_EXISTS
    };

    enum ErrorData
    {
        SUCCESS,
        DONT_SECTION,
        DONT_VARIABLE
    };
private:

    ErrorData getVariable(const std::string& section, const std::string& variable, std::string& answer) const;

    ErrorParser parse(const std::string& path);

    std::vector<Section> _data;
};