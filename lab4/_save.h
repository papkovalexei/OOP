#ifndef H_SAVE
#define H_SAVE

#include <experimental/filesystem>
#include <vector>

namespace fs = std::experimental::filesystem;

class _save
{
public:
    virtual void prepare_data(const fs::path place) = 0;
    virtual void clear_trash(const fs::path place) = 0;
    virtual void remake(const fs::path place) = 0;
    virtual void save(const std::vector<fs::path>& files, fs::path to) = 0;
protected:
};

#endif