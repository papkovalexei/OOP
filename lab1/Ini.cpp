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
    std::string now_sect = "";

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
                        {
                            if (_data.count(str) != 0)
                                return COLLISION_NAME;
                            now_sect = buffer;
                            _data[buffer].setName(buffer);
                        }
                    }
                    else
                    {
                        if (_data.count(str) != 0)
                                return COLLISION_NAME;
                        _data[str].setName(str);  
                        now_sect = str;
                    }
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
                    

                        if (!_data[now_sect].addVariable(variable))
                        {
                            return COLLISION_NAME;
                        }
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
    for (auto it = _data.begin(); it != _data.end(); it++)
    {
        std::cout << (*it).first;
    
        for (auto it1 = (*it).second.getData().begin(); it1 != (*it).second.getData().end(); it++)
        {
            std::cout << (*it1).first << "=" << (*it1).second << std::endl;
        }
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

    if (_data.find(section) != _data.end())
    {
        flag_section = true;
        need_section = (*_data.find(section)).second;
    }

    if (flag_section)
    {
        if (need_section.getData().find(variable) != need_section.getData().end())
        {
            flag_variable = true;
            answer = (*need_section.getData().find(variable)).second;
        }
    }
       
    if (flag_variable && flag_section)
        return ErrorData::SUCCESS;
    else if (!flag_variable)
        return ErrorData::DONT_VARIABLE;
    else if (!flag_section)
        return ErrorData::DONT_SECTION;
    return ErrorData::ERROR;
}

std::string Ini::getString(const std::string& section, const std::string& variable) const
{
    std::string answer = "";;

    ErrorData code = getVariable(section, variable, answer);

    if (code == ErrorData::DONT_SECTION)
    {
        std::cerr << "Doesn't exists section: " << section << std::endl;
        throw ErrorData::DONT_SECTION;
    }
    else if (code == ErrorData::DONT_VARIABLE)
    {
        std::cerr << "Doesn't exists variable: " << variable << std::endl;
        throw ErrorData::DONT_VARIABLE;
    }
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
        {
            std::cerr << section << "::" << variable << ": not float" << std::endl;
            throw ErrorData::ERROR;
        }
    }
    else if (code == ErrorData::DONT_SECTION)
    {
        std::cerr << "Doesn't exists section: " << section << std::endl;
        throw ErrorData::DONT_SECTION;
    }
    else if (code == ErrorData::DONT_VARIABLE)
    {
        std::cerr << "Doesn't exists variable: " << variable << std::endl;
        throw ErrorData::DONT_SECTION;
    }
    return 0.0;
}

int Ini::getInteger(const std::string& section, const std::string& variable)const
{
    std::string answer;

    ErrorData code = getVariable(section, variable, answer);

    if (code == ErrorData::SUCCESS)
    {
        if (isIntegerNumber(answer))
            return std::atoi(answer.c_str());
        else
        {
            std::cerr << section << "::" << variable << ": not integer" << std::endl;
            throw ErrorData::ERROR;
        }
    }
    else if (code == ErrorData::DONT_SECTION)
    {
        std::cerr << "Doesn't exists section: " << section << std::endl;
        throw ErrorData::DONT_SECTION;
    }
    else if (code == ErrorData::DONT_VARIABLE)
    {
        std::cerr << "Doesn't exists variable: " << variable << std::endl;
        throw ErrorData::DONT_VARIABLE;
    }

    return 0;
}