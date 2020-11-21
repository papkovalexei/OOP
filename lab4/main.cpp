#include <iostream>

#include "system_backup.h"

#define PATH_HOLDER_FILE "/home/alexei/labs/OOP/lab4/holder_file/"
#define PATH_HOLDER_BACKUP "/home/alexei/labs/OOP/lab4/holder_backup/"

int main()
{
    system_backup sys;

    int id = sys.create_backup(PATH_HOLDER_FILE, PATH_HOLDER_BACKUP, MODE_SAVING::ARCHIVE_STORAGE);
    time_t time1 = time(0);
    std::cout << time1 << std::endl;
    cleaner clean{0, 0, time1};

    sys.set_cleaner(id, &clean);

    sys.create_restore_point_base(id);  
    sys.create_restore_point_base(id);
    sys.create_restore_point_inc(id);
    sys.create_restore_point_inc(id);
    sys.create_restore_point_base(id);
    sys.create_restore_point_base(id);

    sys.print(id);

    //sys.clean(id);

    return 0;
}