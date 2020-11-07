#ifndef H_RESTORE_POINT
#define H_RESTORE_POINT

#include <vector>
#include <ctime>
#include <iostream>

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
        for (auto& file : files)
            _size += file.size;
    }

    int get_id() const
    {
        return _id;
    }

    int get_prev_id() const
    {
        return _prev_id;
    }

    const std::vector<file>&  get_files() const
    {
        return _files;
    }

    friend std::ostream& operator<<(std::ostream& os, const restore_point& point)
    {
        time_t cast_time = point._creation_time;

        os << "Time create: " << ctime(&cast_time);
        os << "ID: " << point._id << "   Size: " << point._size << std::endl;

        if (point._prev_id == -1)
            os << "Basic point" << std::endl;
        else
            os << "Inc. point, prevID: " << point._prev_id << std::endl;

        for (auto& file : point._files)
            os << file << std::endl;

        return os;
    }

private:
    std::vector<file> _files;
    time_t _creation_time;
    int _size, _id, _prev_id;
};

#endif