#ifndef H_SAVE_ARHICVE
#define H_SAVE_ARHICVE

#include <regex>
#include <iostream>

#include "_save.h"

class save_archive : public _save
{
public:
    save_archive(std::string name)
        : _name(name)
    {}

    void prepare_data(const fs::path place) override
    {
        fs::path path_archive(place);

        path_archive += _name;
        path_archive += ".tar";

        std::string command = "tar -xvf ";
        command += path_archive;
        command += " -C ";
        command += place;
        command += " --level=1";

        system(command.c_str());

        fs::remove(path_archive);
    }

    void clear_trash(const fs::path place) override
    {
        for (auto& file : fs::directory_iterator(place))
            if (!std::regex_match(file.path().filename().c_str(), std::regex(".*\\.tar")))
                fs::remove_all(file);
    }

    void save(const std::vector<fs::path>& files, fs::path to) override
    {
        fs::create_directories(to);

        for (auto& file : files)
            fs::copy(file, to);
        _create_archive(to.parent_path().parent_path());
    }

    void remake(fs::path place) override
    {
        _create_archive(place);
    }
private:

    void _create_archive(fs::path place)
    {
        fs::path path_archive(place);
        path_archive += "/";
        path_archive += _name;
        path_archive += ".tar";

        std::string command = "tar -cf ";

        command += path_archive;
        command += " -C ";
        command += place;
        command += " ./";

        system(command.c_str());
    }

    std::string _name;
};

#endif