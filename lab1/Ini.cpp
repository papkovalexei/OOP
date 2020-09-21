#include "Ini.h"

Ini::Ini() 
{
    flag_okay = false;
}

Ini::Ini(const std::string& path)
{
    flag_okay = false;
    load(path);
}

void Ini::load(const std::string& path)
{
    if (std::regex_match(path, std::regex("[a-zA-Z_0-9]*\\.ini")))
    {
        ErrorParser check_error = parse(path);

        if (check_error == INCORRECT_FORMAT)
            std::cerr << "Incorrect .ini format" << std::endl;
        else if (check_error == FILE_NOT_EXISTS)
            std::cerr << "File doesn't exists" << std::endl;
        else if (check_error == COLLISION_NAME)
            std::cerr << "Collision name's" << std::endl;
        else if (check_error == GOOD)
            flag_okay = true;
    }
    else
    {
        std::cerr << "Don't .ini file" << std::endl;
    }
}

bool Ini::is_okay() const
{
    return flag_okay;
}

Ini::ErrorParser Ini::parse(const std::string& path)
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
                        if (_data.size() == 0)
                            return INCORRECT_SECTION;

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

                        for (int j = 0; j < _data[_data.size() - 1].size(); j++)
                        {
                            if (_data[_data.size() - 1][j].first == variable.first)
                                return COLLISION_NAME;
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

    input.close();

    return ErrorParser::GOOD;
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
    if (str.size() == 0)
        return false;

    for (int i = 0; i < str.size(); i++)
        if (str[i] < '0' || str[i] > '9')
            return false;

    return true;
}

bool isFloatNumber(std::string str)
{
    if (str.size() == 0)
        return false;
    if (str[0] == '.')
        return false;
    int count_dot = 0;

    for (int i = 0; i < str.size(); i++)
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
            return false;
        else if (str[i] == '.')
        {
            count_dot++;

            if (count_dot > 1)
                return false;
        }

    return true;
}

Ini::ErrorData Ini::getVariable(const std::string& section, const std::string& variable, std::string& answer) const
{
    bool flag_section = false, flag_variable = false, flag_format = false;
    int code = 0;
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
    
    if (flag_section)
        for (int i = 0; i < need_section.size(); i++)
        {
            if (need_section[i].first == variable)
            {
                flag_variable = true;
            
                answer = need_section[i].second;
            }
        }
    if (flag_variable && flag_section)
        return ErrorData::SUCCESS;
    else if (!flag_variable)
        return ErrorData::DONT_VARIABLE;
    else if (!flag_section)
        return ErrorData::DONT_SECTION;
}

std::string Ini::getString(const std::string& section, const std::string& variable) const
{
    std::string answer = "";;

    ErrorData code = getVariable(section, variable, answer);

    if (code == ErrorData::DONT_SECTION)
        std::cerr << "Doesn't exists section: " << section << std::endl;
    else if (code == ErrorData::DONT_VARIABLE)
        std::cerr << "Doesn't exists variable: " << variable << std::endl;
    return answer;
}

float Ini::getFloat(const std::string& section, const std::string& variable) const
{
    std::string answer;

    ErrorData code = getVariable(section, variable, answer);

    if (code == ErrorData::SUCCESS)
    {
        if (isFloatNumber(answer))
            return std::atof(answer.c_str());
        else
            std::cerr << section << "::" << variable << ": not float" << std::endl;
    }
    else if (code == ErrorData::DONT_SECTION)
        std::cerr << "Doesn't exists section: " << section << std::endl;
    else if (code == ErrorData::DONT_VARIABLE)
        std::cerr << "Doesn't exists variable: " << variable << std::endl;
    return 0.0;
}

int Ini::getInteger(const std::string& section, const std::string& variable) const
{
    std::string answer;

    ErrorData code = getVariable(section, variable, answer);

    if (code == ErrorData::SUCCESS)
    {
        if (isIntegerNumber(answer))
            return std::atoi(answer.c_str());
        else
            std::cerr << section << "::" << variable << ": not integer" << std::endl;
    }
    else if (code == ErrorData::DONT_SECTION)
        std::cerr << "Doesn't exists section: " << section << std::endl;
    else if (code == ErrorData::DONT_VARIABLE)
        std::cerr << "Doesn't exists variable: " << variable << std::endl;

    return 0;
}