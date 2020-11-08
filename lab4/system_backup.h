#ifndef H_SYSTEM_BACKUP
#define H_SYSTEM_BACKUP

#include <iostream>
#include <vector>
#include <algorithm>

#include "backup.h"

#define MODE_COUNT 1
#define MODE_DATE 2
#define MODE_SIZE 4

#define WHEN_ALL 1
#define WHEN_ONE 2

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
        _remove_restore(id, offset);
    }

    void clear_restore_point_time(int id, time_t time)
    {
        int offset = _clear_restore_point_time(id, time);
        _remove_restore(id, offset);
    }

    void clear_restore_point_size(int id, int size)
    {
        int offset = _clear_restore_point_size(id, size);
        _remove_restore(id, offset);
    }

    void clear_gybrid_restore_point(int id, int mode, int when, time_t time, int size, int count)
    {
        std::vector<int> points_offset;

        if (mode | MODE_COUNT == mode)
        {
            points_offset.push_back(_clear_restore_point_count(id, count));
            std::cout << "Offset: " << points_offset[points_offset.size() - 1] << std::endl;
        }

        if (mode | MODE_DATE == mode)
            points_offset.push_back(_clear_restore_point_time(id, time));

        if (mode | MODE_SIZE == mode)
        {
            points_offset.push_back(_clear_restore_point_size(id, size));
        }

        int point_remove;

        if (when == WHEN_ALL)
            point_remove = (*std::min_element(points_offset.begin(), points_offset.end()));
        else
            point_remove = (*std::max_element(points_offset.begin(), points_offset.end()));
        std::cout << "point remove: " << point_remove << std::endl;
        _remove_restore(id, point_remove);
    }
private:
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
            if (buffer_count + 1 == count)
            {
                while (points[i].get_prev_id() != -1)
                {
                    buffer_count++;
                    std::cerr << "Restore problems in backup(count): " << id << std::endl;
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
                {
                    std::cerr << "Restore problems in backup(time): " << id << std::endl;
                    i--;
                }

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
                int buffer_offset = 0;

                while (points[i].get_prev_id() != -1)
                {
                    buffer_offset = 1;
                    sum_size += points[i].get_size();
                    std::cerr << "Restore problems in backup(size): " << id << std::endl;
                    i--;
                }

                offset = i - buffer_offset;
                break;
            }
            else if (sum_size + points[i].get_size() == size)
            {
                if (points[i].get_prev_id() == -1)
                {
                    sum_size += points[i].get_size();
                    i--;
                }
                else
                {
                    bool flag_warning = true;
                    while (points[i].get_prev_id() != -1)
                    {
                        sum_size += points[i].get_size();
                        if (flag_warning)
                        {
                            std::cerr << "Restore problems in backup(size): " << id << std::endl;
                            flag_warning = false;
                        }
                        i--;
                    }
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
        std::cout << "Offset: " << offset << std::endl;
        return offset;
    }


    static int _id_put;
    std::map<int, backup> _backups;
};

int system_backup::_id_put = 0;

#endif