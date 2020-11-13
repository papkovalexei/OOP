#ifndef H_RESTORE_POINT_BASE
#define H_RESTORE_POINT_BASE

#include "_restore_point.h"

class restore_point_base : public _restore_point
{
public:
    restore_point_base(const std::vector<fs::path>& files)
        : _restore_point(files)
    {
        for (const auto& file : files)
            _size += fs::file_size(file);
    }

private:

};

#endif