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

    void addVariable(const std::pair<std::string, std::string>& variable);

    std::string getName() const;
    void setName(const std::string& name);

    const std::pair<std::string, std::string>& operator[](size_t position) const;

    size_t size() const;
private:
    std::string _name;
    std::vector<std::pair<std::string, std::string>> _variable_data;
};
