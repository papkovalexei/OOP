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


    void clear_restore_point_count(int id, int count)
    {
        int offset = _clear_restore_point_count(id, count);
        _check_offset(id, offset);
        _remove_restore(id, offset);
    }

    void clear_restore_point_time(int id, time_t time)
    {
        int offset = _clear_restore_point_time(id, time);
        _check_offset(id, offset);
        _remove_restore(id, offset);
    }

    void clear_restore_point_size(int id, int size)
    {
        int offset = _clear_restore_point_size(id, size);
        std::cout << offset << " offset\n";
        _check_offset(id, offset);
        _remove_restore(id, offset);
    }

private:
    void _check_offset(int id, int offset)
    {
        if (offset == -1)
        {
            std::cerr << "Some problems in backup: " << id << std::endl << "Don't can delete restore" << std::endl; 
        }
    }

    void _remove_restore(int id, int offset)
    {
        auto& points = _backups[id].get_all_points();

        for (int i = 0; i <= offset; i++)
            points.erase(points.begin());
    }

    int _clear_restore_point_count(int id, int count)
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
            {
                buffer_count++;

                if (i == 0)
                    offset = -2;
            }
        }

        return offset;
    }

    int _clear_restore_point_time(int id, time_t time)
    {
        auto& points = _backups[id].get_all_points();
        int offset = 0;

        for (int i = points.size() - 1; i >= 0; i--)
        {
            if (points[i].get_time() < time)
            {
                while (points[i].get_prev_id() != -1)
                    i--;

                offset = i - 1;
                break;
            }
            else
            {
                 if (i == 0)
                    offset = -2;
            }
        }

        return offset;
    }

    int _clear_restore_point_size(int id, int size)
    {
        auto& points = _backups[id].get_all_points();
        int offset = 0, sum_size = 0;

        for (int i = points.size() - 1; i >= 0; i--)
        {
            if (sum_size + points[i].get_size() > size)
            {
                while (points[i].get_prev_id() != -1)
                {
                    sum_size += points[i].get_size();
                    i--;
                }

                offset = i - 1;
                break;
            }
            else if (sum_size + points[i].get_size() == size)
            {
                sum_size += points[i].get_size();
                i--;

                while (points[i].get_prev_id() != -1)
                {
                    sum_size += points[i].get_size();
                    i--;
                }

                offset = i - 1;
                break;
            }
            else
            {
                sum_size += points[i].get_size();

                 if (i == 0)
                    offset = -2;
            }
        }

        return offset;
    }


    static int _id_put;
    std::map<int, backup> _backups;
};

int system_backup::_id_put = 0;

#endif