#include <iostream>
#include <vector>

#include "file.h"
#include "system_backup.h"

int main()
{
    std::vector<file> files;

    files.push_back(file("File1.txt", 20));
    files.push_back(file("File2.pdf", 30));
    files.push_back(file("File3.txt", 210));
    files.push_back(file("File4.cpp", 2430));

    system_backup sys;

    int id = sys.create_backup(files);

    sys.remove_file(id, file("File1.txt", 20));

    sys.create_restore_point_base(id);

    sys.add_file(id, file("new.txt", 13));
    sys.create_restor_point_increment(id);

    sys.print_backup(id);

    return 0;
}