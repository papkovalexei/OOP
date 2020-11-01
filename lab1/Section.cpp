#include "Section.h"

Section::Section() 
{
    _name = "";
}

Section::Section(const std::string& name)
{
    _name = name;
}

std::string Section::getName() const 
{
    return _name;
}

void Section::setName(const std::string& name)
{
    _name = name;
}

bool Section::addVariable(const std::pair<std::string, std::string>& variable)
{
    if (_variable_data.count(variable.first) != 0)
        return false;
    _variable_data[variable.first] = variable.second;
    return true;
}

size_t Section::size() const
{
    return _variable_data.size();
}

std::map<std::string, std::string> Section::getData() const
{
    return _variable_data;
}