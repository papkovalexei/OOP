#ifndef H_RESTORE_POINT_BASE
#define H_RESTORE_POINT_BASE

#include "_restore_point.h"

class restore_point_base : public _restore_point
{
public:
    restore_point_base(const fs::path& path)
        : _restore_point()
    {
        _path = path;
        
        for (auto& file : fs::directory_iterator(path))
        {
            _files.push_back(file);
            _size += fs::file_size(file);
        }
    }
private:
};

#endif