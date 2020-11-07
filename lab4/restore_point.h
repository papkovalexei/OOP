#ifndef H_RESTORE_POINT
#define H_RESTORE_POINT

#include <vector>
#include <ctime>

#include "file.h"

class restore_point
{
public:
    restore_point(const std::vector<file>& files, int id)
        : _files(files), _creation_time(time(0)), _size(0), _id(id), _prev_id(-1)
    {
        for (auto& file : files)
            _size += file.size;
    }

    restore_point(const std::vector<file>& files, int id, int prev_id)
        : _files(files), _creation_time(time(0)), _size(0), _id(id), _prev_id(prev_id)
    {
    }

    int get_id() const
    {
        return _id;
    }

    const std::vector<file>&  get_files() const
    {
        return _files;
    }

private:
    std::vector<file> _files;
    time_t _creation_time;
    int _size, _id, _prev_id;
};

#endif