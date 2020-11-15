#ifndef H_BACKUP
#define H_BACKUP

#include <string>
#include <iostream>
#include <map>

#include "restore_point_base.h"
#include "restore_point_inc.h"

enum MODE_SAVING
{
    ARCHIVE_STORAGE,
    SEPARAT_STORAGE
};

class backup
{
public:
    backup() {}

    backup(const std::string& holder_file, const std::string& holder_backup, MODE_SAVING mode_saving)
        : _holder_file(holder_file), _holder_backup(holder_backup), _creation_time(time(0)), _size(0), _id_points(0), 
            _mode_saving(mode_saving)
    {

    }

    ~backup() {}

    void create_restore_point_base()
    {
        fs::path buffer_path = _get_path(_id_points);

        _points[_id_points] = new restore_point_base(_holder_file);
        _save_data(_points[_id_points]->get_files(), buffer_path);

        _points[_id_points]->reboot_link(buffer_path);
        _size += _points[_id_points++]->get_size();
    }

    void create_restore_point_inc()
    {
        if (_points.empty())
        {
            create_restore_point_base();
        }
        else
        {
            fs::path buffer_path = _get_path(_id_points);

            _points[_id_points] = new restore_point_inc(_holder_file, _points);

            _save_data(_points[_id_points]->get_files(), buffer_path);
            _points[_id_points++]->reboot_link(buffer_path);
        }   
    }
private: 
    fs::path _get_path(int _id_point)
    {
        fs::path new_directory(_holder_backup);
        new_directory += "/";
        new_directory += std::to_string(_id_point);
        new_directory += "/";

        return new_directory;
    }

    void _save_data(const std::vector<fs::path>& files, fs::path to)
    {
        fs::create_directories(to);

        for (auto& file : files)
            fs::copy(file, to);
        
        if (_mode_saving == MODE_SAVING::ARCHIVE_STORAGE)
        {
            fs::path path_archive(_holder_backup);
            path_archive += std::to_string(_creation_time);
            path_archive += ".tar";

            bool exist_archive = fs::exists(path_archive);

        }
    }

    std::map<int, _restore_point*> _points;
    fs::path _holder_file;
    fs::path _holder_backup;
    MODE_SAVING _mode_saving;
    size_t _size;
    time_t _creation_time;
    int _id_points;
};

#endif