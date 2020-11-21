#include <iostream>

#include "system_backup.h"
#include "save_archive.h"
#include "save_base.h"

#define PATH_HOLDER_FILE "/home/alexei/labs/OOP/lab4/holder_file/"
#define PATH_HOLDER_BACKUP "/home/alexei/labs/OOP/lab4/holder_backup/"

int main()
{
    system_backup sys;
    time_t time1 = time(0);
    cleaner clean{-1, 2, -1};
    save_base save;
    save_archive save_arc(std::to_string(time1));

    int id = sys.create_backup(PATH_HOLDER_BACKUP, &save_arc);
    
    for (auto& file : fs::directory_iterator(PATH_HOLDER_FILE))
        sys.add_file(id, file.path());

    sys.set_cleaner(id, &clean);

    sys.create_restore_point_base(id);  
    sys.create_restore_point_base(id);
    sys.create_restore_point_inc(id);
    sys.create_restore_point_inc(id);
    sys.create_restore_point_base(id);
    sys.create_restore_point_base(id);

    sys.print(id);

    sys.clear_point(id);

    return 0;
}