#ifndef H_BASE_SAVE
#define H_BASE_SAVE

#include "_save.h"

class save_base : public _save
{
    void save(const std::vector<fs::path>& files, fs::path to) override
    {  
        fs::create_directories(to);

        for (auto& file : files)
            fs::copy(file, to);
    }

    void prepare_data(const fs::path place) override
    {

    }

    void clear_trash(const fs::path place) override
    {

    }

    void remake(const fs::path place) override
    {
        
    }
};

#endif