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

enum MODE_SAVING
{
    ARCHIVE_STORAGE,
    SEPARAT_STORAGE
};

class backup
{
public:
    backup() {}

    backup(const std::string& holder_backup, MODE_SAVING mode_saving)
        : _holder_backup(holder_backup), _creation_time(time(0)), _size(0), _id_points(0), 
            _mode_saving(mode_saving)
    {

    }

    ~backup() {}

    void create_restore_point_base()
    {
        fs::path buffer_path = _get_path(_id_points);

        _points[_id_points] = new restore_point_base(_files);
        _save_data(_points[_id_points]->get_files(), buffer_path);

        _points[_id_points]->reboot_link(buffer_path);
        _size += _points[_id_points++]->get_size();
        _clear_cache();

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
            if (_mode_saving == MODE_SAVING::ARCHIVE_STORAGE)
                _create_cache();

            fs::path buffer_path = _get_path(_id_points);

            _points[_id_points] = new restore_point_inc(_files, _points);

            _save_data(_points[_id_points]->get_files(), buffer_path);
            _points[_id_points++]->reboot_link(buffer_path);
            _clear_cache();
            std::cout << _size << std::endl;
        }   
    }

    void set_cleaner(cleaner* clean)
    {
        _cleaner = clean;
    }

    void clean()
    {
        auto delete_points = _cleaner->clean_time(_points);

        for (auto it = delete_points.begin(); it != delete_points.end(); it++)
        {
            _points[(**it).first]->~_restore_point();
            _points.erase((*it));
        }
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

            std::string command;

            bool exist_archive = fs::exists(path_archive);

            if (exist_archive)
                command = "tar -rvf ";
            else
                command = "tar -cf ";

            command += path_archive;
            command += " -C ";
            command += _holder_backup;
            command += " ./";

            system(command.c_str());
        }
    }

    void _clear_cache()
    {
        if (_mode_saving == MODE_SAVING::ARCHIVE_STORAGE)
        {
            for (auto& file : fs::directory_iterator(_holder_backup))
                if (!std::regex_match(file.path().filename().c_str(), std::regex(".*\\.tar")))
                    fs::remove_all(file);
        }
    }

    void _create_cache()
    {
        fs::path path_archive(_holder_backup);

        path_archive += std::to_string(_creation_time);
        path_archive += ".tar";

        std::string command = "tar -xvf ";
        command += path_archive;
        command += " -C ";
        command += _holder_backup;
        command += " --level=1";

        system(command.c_str());

        fs::remove(path_archive);
    }

    std::map<int, _restore_point*> _points;
    std::vector<fs::path> _files;
    fs::path _holder_backup;
    MODE_SAVING _mode_saving;
    size_t _size;
    time_t _creation_time;
    int _id_points;
    cleaner* _cleaner;
};

#endif