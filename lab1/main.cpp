#include <iostream>

#include "Ini.h"

int main()
{
    Ini ini("test.ini");

    ini.getInteger("[Profile1]", "Default");

    return 0;
}