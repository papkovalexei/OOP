#include <iostream>

#include "Ini.h"

int main()
{
    Ini ini("test.isni");

    std::cout << ini.getString("[Profile1]", "Name") << std::endl;
    std::cout << ini.getInteger("[Profile1]", "Default") << std::endl;
    std::cout << ini.getFloat("[Profile1]", "IsRelative") << std::endl;
    

    return 0;
}