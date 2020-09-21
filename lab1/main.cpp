#include <iostream>

#include "Ini.h"

int main()
{
    Ini ini("test.ini");

    if (ini.is_okay())
    {
        std::cout << ini.getString("[Profile1]", "Name") << std::endl;
        std::cout << ini.getInteger("[Profile1]", "Default") << std::endl;
        std::cout << ini.getFloat("[Profile1]", "IsRelative") << std::endl;
    }
    else
        std::cout << "Some error\n";

    return 0;
}