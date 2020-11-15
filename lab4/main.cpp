#include <iostream>

#include "system_backup.h"

#define PATH_HOLDER_FILE "/home/alexei/labs/OOP/lab4/holder_file/"
#define PATH_HOLDER_BACKUP "/home/alexei/labs/OOP/lab4/holder_backup/"

int main()
{
    system_backup sys;

    int id = sys.create_backup(PATH_HOLDER_FILE, PATH_HOLDER_BACKUP, MODE_SAVING::SEPARAT_STORAGE);
    sys.create_restore_point_base(id);
    
    sys.create_restore_point_base(id);
    
    sys.create_restore_point_inc(id);
    
    sys.create_restore_point_inc(id);
    
    sys.create_restore_point_base(id);

    return 0;
}