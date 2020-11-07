#ifndef H_SYSTEM_BACKUP
#define H_SYSTEM_BACKUP

#include <iostream>
#include <vector>

#include "backup.h"

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

    void print_backup(int id) const
    {
        std::cout << _backups[id];
    }

private:
    static int _id_put;
    std::vector<backup> _backups;
};

int system_backup::_id_put = 0;

#endif