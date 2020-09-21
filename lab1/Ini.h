#include <iostream>
#include <exception>
#include <vector>
#include <fstream>

#include "Section.h"

class Ini 
{
public:

    enum ErrorParser
    {
        GOOD,
        INCORRECT_FORMAT,
        FILE_NOT_EXISTS,
        INCORRECT_SECTION,
        COLLISION_NAME
    };

    enum ErrorData
    {
        SUCCESS,
        DONT_SECTION,
        DONT_VARIABLE
    };

    Ini();
    Ini(const std::string& path);

    void load(const std::string& path);

    int getInteger(const std::string& section, const std::string& variable) const;
    float getFloat(const std::string& section, const std::string& variable) const;
    bool is_okay() const;
    std::string getString(const std::string& section, const std::string& variable) const;

    void show() const;

private:

    ErrorData getVariable(const std::string& section, const std::string& variable, std::string& answer) const;
    ErrorParser parse(const std::string& path);

    std::vector<Section> _data;
    bool flag_okay;
};