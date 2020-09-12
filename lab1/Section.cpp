#include "Section.h"

Section::Section() {}

Section::Section(const std::string& name, const std::vector<std::pair<std::string, std::string>>& variable_data)
{
    _name = name;
    _variable_data = variable_data;
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

void Section::addVariable(const std::pair<std::string, std::string>& variable)
{
    _variable_data.push_back(variable);
}

size_t Section::size() const
{
    return _variable_data.size();
}

const std::pair<std::string, std::string>& Section::operator[](size_t position) const
{
    return _variable_data[position];
}