#include <iostream>
#include <vector>
#include <regex>
#include <string>

class Section
{
public:
    Section();

    Section(const std::string& name, const std::vector<std::pair<std::string, std::string>>& variable_data);
    Section(const std::string& name);

    bool addVariable(const std::pair<std::string, std::string>& variable);

    std::string getName() const;
    void setName(const std::string& name);

    size_t size() const;

    std::map<std::string, std::string> getData() const;
private:
    std::string _name;
    std::map<std::string, std::string> _variable_data;
};
