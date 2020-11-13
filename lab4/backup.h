#ifndef H_BACKUP
#define H_BACKUP

#include <string>
#include <iostream>
#include <map>

#include "restore_point_base.h"

class backup
{
public:
    backup() {}

    backup(const std::string& holder_file, const std::string& holder_backup)
        : _holder_file(holder_file), _holder_backup(holder_backup), _creation_time(time(0)), _size(0), _id_points(0)
    {

    }

    void create_restore_point_base()
    {
        std::vector<fs::path> buffer;

        for (auto& file : fs::directory_iterator(_holder_file))
            buffer.push_back(file.path());

        _points[_id_points] = new restore_point_base(buffer);

        _size += _points[_id_points]->get_size();

        std::cout << "size: " << _size << std::endl;

        _save_point(_id_points);

        _id_points++;
    }

    ~backup() {}
private: 
    void _save_point(int _id_point)
    {
        fs::path new_directory(_holder_backup);
        new_directory += "/";
        new_directory += std::to_string(_id_point);
        new_directory += "/";
    
        fs::create_directories(new_directory);

        for (auto& file : _points[_id_points]->get_files())
        {
            fs::copy(file, new_directory);
        }
    }

    std::map<int, _restore_point*> _points;
    fs::path _holder_file;
    fs::path _holder_backup;
    size_t _size;
    time_t _creation_time;
    int _id_points;
};

#endif