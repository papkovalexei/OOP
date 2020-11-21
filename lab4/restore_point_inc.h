#ifndef H_RESTORE_POINT_INC
#define H_RESTORE_POINT_INC

#include <map>
#include <vector>

#include "_restore_point.h"
#include "restore_point_base.h"

class restore_point_inc : public _restore_point
{
public:
    restore_point_inc(const std::vector<fs::path>& files, std::map<int, _restore_point*>& old_points) // old_files - reference to base->inc->inc point
        : _restore_point()
    {
        fs::path path = "buffer/";

        fs::create_directory(path);

        for (auto& file : files)
            fs::copy(file, path);

        std::string command = "diff -Nar ";

        for (auto it = old_points.end();; it--)
        {
            if (it == old_points.end())
                continue;
            if (dynamic_cast<restore_point_base*>((*it).second))
            {
                bool flag_start = true;

                for (auto it1 = it; it1 != old_points.end(); it1++)
                {
                    command = "diff -Nar ";
                    command += (*it1).second->get_path();

                    if (flag_start)
                    {
                        command += " ";
                        command += path;

                        _files.push_back(std::to_string(_creation_time));

                        flag_start = false;
                    }
                    else
                    {
                        command += " /";
                        command += std::to_string(_creation_time);

                    }

                    command += " > ";
                    command += std::to_string(_creation_time);
                    system(command.c_str());
                    command.clear();
                }

                break;
            }

            if (it == old_points.begin())
                break;
        }
        fs::remove_all(path);

        _size += fs::file_size(std::to_string(_creation_time));
    }

    void reboot_link(const fs::path& path) override
    {
        std::string command = "rm ";
        command += std::to_string(_creation_time);

        system(command.c_str());

        _path = path;
    }

private:
};

#endif
