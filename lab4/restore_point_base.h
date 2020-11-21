#ifndef H_RESTORE_POINT_BASE
#define H_RESTORE_POINT_BASE

#include <vector>

#include "_restore_point.h"

class restore_point_base : public _restore_point
{
public:
    restore_point_base(const std::vector<fs::path>& files)
        : _restore_point()
    {   
        for (auto& file : files)
        {
            _files.push_back(file);
            _size += fs::file_size(file);
        }
    }
private:
};

#endif