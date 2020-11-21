#ifndef H_RESTORE_POINT
#define H_RESTORE_POINT

#include <experimental/filesystem>
#include <vector>
#include <ctime>
#include <iostream>

namespace fs = std::experimental::filesystem;

class _restore_point
{
public:
    _restore_point()
        : _creation_time(time(0)), _size(0)
    {
        
    }

    virtual ~_restore_point()
    {
        std::cout << "~restore_point() " << _path << std::endl;

        fs::remove_all(_path);
    }

    size_t get_size() const
    {
        return _size;
    }

    time_t get_creation_time() const
    {
        return _creation_time;
    }

    const std::vector<fs::path>& get_files() 
    {
        return _files;
    }

    fs::path get_path() const
    {
        return _path;
    }

    virtual void reboot_link(const fs::path& path)
    {
        _path = path;
        _files.clear();
        
        for (auto& file : fs::directory_iterator(path))
            _files.push_back(file);
    }
protected:
    std::vector<fs::path> _files;
    fs::path _path;
    time_t _creation_time;
    size_t _size;
    int _id, _prev_id;
};

#endif