#ifndef H_BACKUP
#define H_BACKUP

#include <string>
#include <iostream>
#include <regex>
#include <regex.h>
#include <map>

#include "restore_point_base.h"
#include "restore_point_inc.h"
#include "cleaner.h"
#include "_save.h"

class backup
{
public:
    backup() {}

    backup(const std::string& holder_backup, _save* saver)
        : _holder_backup(holder_backup), _creation_time(time(0)), _size(0), _id_points(0), _saver(saver)
    {}

    ~backup() {}

    void create_restore_point_base()
    {
        fs::path buffer_path = _get_path(_id_points);

        _points[_id_points] = new restore_point_base(_files);

        _saver->prepare_data(_holder_backup);
        _saver->save(_points[_id_points]->get_files(), buffer_path);

        _points[_id_points]->reboot_link(buffer_path);
        _size += _points[_id_points++]->get_size();

        _saver->clear_trash(_holder_backup);

        std::cout << _size << std::endl;
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

            _points[_id_points] = new restore_point_inc(_files, _points);

            _saver->prepare_data(_holder_backup);
            _saver->save(_points[_id_points]->get_files(), buffer_path);

            _points[_id_points++]->reboot_link(buffer_path);

            _saver->clear_trash(_holder_backup);
        }   
    }

    void set_cleaner(cleaner* clean)
    {
        _cleaner = clean;
    }

    void clear_point()
    {
        _saver->prepare_data(_holder_backup);

        auto delete_points = _cleaner->clear_point(_points);
        
        for (auto it = delete_points.begin(); it != delete_points.end(); it++)
        {
            _points[(**it).first]->~_restore_point();
            _points.erase((*it));
        }

        _saver->remake(_holder_backup);
        _saver->clear_trash(_holder_backup);
    }

    void add_file(const fs::path& file)
    {
        _files.push_back(file);
    }

    void remove_file(const fs::path& file)
    {
        for (auto it = _files.begin(); it != _files.end(); it++)
        {
            if ((*it) == file)
            {
                _files.erase(it);
                break;
            }
        }
    }

    friend std::ostream& operator<<(std::ostream& os, backup& back)
    {
        for (auto it = back._points.begin(); it != back._points.end(); it++)
            os << "ID: " << (*it).first << "  size: " << (*it).second->get_size() << "  Time: " << (*it).second->get_creation_time() << " path: " << (*it).second->get_path() << std::endl;
        return os;
    }
private:
    fs::path _get_path(int _id_point)
    {
        fs::path new_directory(_holder_backup);
        new_directory += std::to_string(_id_point);
        new_directory += "/";

        return new_directory;
    }

    std::map<int, _restore_point*> _points;
    std::vector<fs::path> _files;
    fs::path _holder_backup;
    size_t _size;
    time_t _creation_time;
    int _id_points;

    _save* _saver;
    cleaner* _cleaner;
};

#endif