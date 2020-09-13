#include "Ini.h"

Ini::Ini() {}

Ini::Ini(const std::string& path)
{
   load(path);
}

void Ini::load(const std::string& path)
{
     Error check_error = parse(path);

    if (check_error == INCORRECT_FORMAT)
        std::cerr << "Incorrect .ini format" << std::endl;
    else if (check_error == FILE_NOT_EXISTS)
        std::cerr << "File doesn't exists" << std::endl;
}

Ini::Error Ini::parse(const std::string& path)
{
    std::ifstream input(path);

    if (input.is_open())
    {
        std::pair<std::string, std::string> variable;
        std::string str;

        while (std::getline(input, str))
        {
            if (str[0] == '[')
            {
                if (std::regex_match(str, std::regex("\\[[a-zA-Z_0-9]*\\]"))
                    || std::regex_match(str, std::regex("\\[[a-zA-Z_0-9]*\\] *;.*")))
                {
                    if (std::find(str.begin(), str.end(), ';') != str.end())
                    {
                        std::string buffer = "";

                        for (int i = 0; i < str.size(); i++)
                        {
                            if (str[i] != ']')
                                buffer += str[i];
                            else
                            {
                                buffer += ']';
                                break;
                            }
                        }
                        _data.push_back(Section(buffer));
                    }
                    else
                        _data.push_back(Section(str));
                }
                else
                {
                    input.close();
                    _data.clear();

                    return INCORRECT_FORMAT;
                }
            }
            else if (str.size() != 0)
            {
                if (str[0] == ';')
                    continue;
                else
                {
                    if (std::regex_match(str, std::regex("[a-zA-Z_0-9\\-]* *= *[a-zA-Z_0-9\\.\\-]*"))
                        || std::regex_match(str, std::regex("[a-zA-Z_0-9\\-]* *= *[a-zA-Z_0-9\\.\\-]* *;.*")))
                    {
                        variable.first = "";
                        variable.second = "";
                        
                        bool flag_is = false;

                        for (int i = 0; i < str.size(); i++)
                        {
                            if (str[i] == ';')
                                break;
                            if (str[i] == ' ')
                                continue;
                            if (str[i] == '=')
                                flag_is = true;                                
                            if (flag_is)
                            {
                                if (str[i] == '=')
                                    continue;
                                variable.second += str[i];
                            }
                            else
                                variable.first += str[i];
                        }

                        _data[_data.size() - 1].addVariable(variable);
                    }
                    else
                    {
                        input.close();
                        _data.clear();

                        return INCORRECT_FORMAT;
                    }
                }
            }
        }        
    }
    else
    {
        _data.clear();
        return FILE_NOT_EXISTS;
    }

    return GOOD;
}

void Ini::show() const
{
    for (int i = 0; i < _data.size(); i++)
    {
        std::cout << _data[i].getName() << std::endl;

        for (int j = 0; j < _data[i].size(); j++)
            std::cout << _data[i][j].first << "=" << _data[i][j].second << std::endl;
        std::cout << std::endl;
    }
}

bool isIntegerNumber(std::string str)
{
    for (int i = 0; i < str.size(); i++)
        if (str[i] < '0' || str[i] > '9')
            return false;

    return true;
}

int Ini::getInteger(std::string section, std::string variable) const
{
    bool flag_section = false, flag_variable = false, flag_format = false;
    int answer = 0;
    Section need_section;

    for (int i = 0; i < _data.size(); i++)
    {
        if (_data[i].getName() == section)
        {
            flag_section = true;
            need_section = _data[i];
            break;
        }
    }
    
    for (int i = 0; i < need_section.size(); i++)
    {
        if (need_section[i].first == variable)
        {
            flag_variable = true;
        
            if (isIntegerNumber(need_section[i].second))
            {
                flag_format = true;
                answer = std::atoi(need_section[i].second.c_str());
            }
            
        }
    }

    if (!flag_section)
        std::cerr << "Doesn't exists section: " << section << std::endl;
    else if (!flag_variable)
        std::cerr << "Doesn't exists variable:" << variable << std::endl;
    else if (!flag_format)
        std::cerr << "It's not integer" << std::endl;

    return answer;
}