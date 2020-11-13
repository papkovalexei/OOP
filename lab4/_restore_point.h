#ifndef H_RESTORE_POINT
#define H_RESTORE_POINT

#include <experimental/filesystem>
#include <vector>
#include <ctime>

namespace fs = std::experimental::filesystem;

class _restore_point
{
public:
    _restore_point()
        : _creation_time(time(0)), _size(0)
    {

    }

    _restore_point(const std::vector<fs::path>& files)
        : _files(files), _creation_time(time(0)), _size(0)
    {
        
    }

    ~_restore_point()
    {
        for (auto& file : _files)
            fs::remove(file);
    }

    size_t get_size() const
    {
        return _size;
    }

    std::vector<fs::path>& get_files()
    {
        return _files;
    }

protected:
    std::vector<fs::path> _files;
    time_t _creation_time;
    size_t _size;
    int _id, _prev_id;
};

#endif