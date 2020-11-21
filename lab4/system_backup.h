#ifndef H_SYSTEM_BACKUP
#define H_SYSTEM_BACKUP

#include <map>
#include <experimental/filesystem>

#include "backup.h"

class system_backup
{
public:
    int create_backup(const std::string& holder_backup, _save* saver)
    {
        _backups[_id_backup] = backup(holder_backup, saver);

        return _id_backup++;
    }

    void create_restore_point_base(int id)
    {
        _backups[id].create_restore_point_base();
    }

    void create_restore_point_inc(int id)
    {
        _backups[id].create_restore_point_inc();
    }

    void set_cleaner(int id, cleaner* clean)
    {
        _backups[id].set_cleaner(clean);
    }

    void add_file(int id, const fs::path& file)
    {
        _backups[id].add_file(file);
    }

    void remove_file(int id, const fs::path& file)
    {
        _backups[id].remove_file(file);
    }

    void print(int id)
    {
        std::cout << _backups[id];
    }

    void clear_point(int id)
    {
        _backups[id].clear_point();
    }

private:
    std::map<int, backup> _backups;
    static int _id_backup;
};

int system_backup::_id_backup = 0;

#endif