#ifndef H_SYSTEM_BACKUP
#define H_SYSTEM_BACKUP

#include <iostream>
#include <vector>

#include "backup.h"

#define MODE_COUNT 1
#define MODE_DATE 2
#define MODE_SIZE 4

class system_backup
{
public:
    system_backup()
    {

    }

    ~system_backup()
    {
        
    }

    int create_backup(const std::vector<file>& files)
    {
        _backups.push_back(backup(files, _id_put));

        return _id_put++;
    }

    void create_restore_point_base(int id)
    {
        _backups[id].create_restore_point_base();
    }

    void create_restor_point_increment(int id)
    {
        _backups[id].create_restore_point_increment();   
    }

    void add_file(int id, const file& file_)
    {
        _backups[id].add_file(file_);
    }

    void remove_file(int id, const file& file_)
    {
        _backups[id].remove_file(file_);
    }

    void print_backup(int id) const
    {
        std::cout << _backups[id];
    }

    int clean_restore_point(int id, int mode)
    {
        return 1;
    }

private:
    static int _id_put;
    std::vector<backup> _backups;
};

int system_backup::_id_put = 0;

#endif