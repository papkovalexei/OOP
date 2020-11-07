#ifndef H_BACKUP
#define H_BACKUP

#include <iostream>
#include <vector>
#include <ctime>
#include <set>
#include <map>

#include "file.h"
#include "restore_point.h"

class backup
{
public:
    backup() 
    {

    }

    backup(const std::vector<file>& files, int id)
        : _new_files(files), _creation_time(time(0)), _backup_size(0), _id(id)
    {
        for (auto& file : files)
            _backup_size += file.size;
    }

    void create_restore_point_base()
    {
        if (!_new_files.empty())
        {
            for (auto& file : _new_files)
                _files.push_back(file);
            _new_files.clear();
        }

        if (_points.empty())
            _points.push_back(restore_point(_files, 0));
        else
            _points.push_back(restore_point(_files, _points.size() - 1));
    }

    void create_restore_point_increment()
    {
        if (_points.empty())
        {
            create_restore_point_base();
            return;
        }

        _points.push_back(restore_point(_new_files, _points.size() - 1, _points[_points.size() - 1].get_id()));

        for (auto& file : _new_files)
            _files.push_back(file);
        _new_files.clear();
    }

    void add_file(const file& file_)
    {
        _new_files.push_back(file_);
    }

    void remove_file(const file& file_)
    {
        for (auto it = _new_files.begin(); it != _new_files.end(); it++)
        {
            if ((*it) == file_)
            {
                _new_files.erase(it);
                break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const backup& back)
    {
        time_t cast_time = back._creation_time;

        os << "Time create: " << ctime(&cast_time);
        os << "ID: " << back._id << "   Size: " << back._backup_size << std::endl;

        for (auto& file : back._files)
            os << file << std::endl;
        os << "--------------------------------" << std::endl;

        for (auto& point : back._points)
            os << point << "--------------------" << std::endl;

        return os;
    }

private:
    std::vector<file> _files;
    std::vector<file> _new_files;
    std::vector<restore_point> _points;
    int _id, _backup_size;
    time_t _creation_time;
};

#endif