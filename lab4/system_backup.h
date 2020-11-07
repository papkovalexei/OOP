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

    int create_backup(const std::vector<file>& files, int mode_storage)
    {
        _backups[_id_put] = backup(files, _id_put, mode_storage);

        return _id_put++;
    }

    void create_restore_point_base(int id)
    {
        _backups[id].create_restore_point_base();
    }

    void create_restore_point_increment(int id)
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

    void print_backup(int id)
    {
        std::cout << _backups[id];
    }

    int clean_restore_point_count(int id, int count)
    {
        auto& points = _backups[id].get_all_points();
        int buffer_count = 0, offset = 0;

        for (int i = points.size() - 1; i >= 0; i--)
        {
            if (buffer_count == count)
            {
                while (points[i].get_prev_id() != -1)
                {
                    buffer_count++;
                    i--;
                }

                offset = i - 1;
                break;
            }
            else
                buffer_count++;
        }

        std::cout << offset << " offset\n";
        return offset;
    }



private:
    static int _id_put;
    std::map<int, backup> _backups;
};

int system_backup::_id_put = 0;

#endif