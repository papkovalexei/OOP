#include <iostream>
#include <vector>

#include "file.h"
#include "system_backup.h"

int main()
{
    std::vector<file> files;

    files.push_back(file("File1.txt", 20));
    files.push_back(file("File2.pdf", 30));
    files.push_back(file("File3.txt", 21));
    files.push_back(file("File4.cpp", 24));

    system_backup sys;

    int id = sys.create_backup(files, SEPARATE_STORAGE);

    sys.remove_file(id, file("File1.txt", 20));

    sys.create_restore_point_base(id); // save file

    sys.add_file(id, file("new.txt", 13)); // can change list files

    sys.create_restore_point_increment(id); // save new file
    sys.create_restore_point_base(id);

    sys.add_file(id, file("new2.txt", 13));
    sys.create_restore_point_base(id);

    sys.add_file(id, file("new3.txt", 13));
    sys.create_restore_point_base(id);

    //sys.print_backup(id);

    sys.clear_restore_point_size(id, 30);

    sys.print_backup(id);

    return 0;
}