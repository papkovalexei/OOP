#ifndef H_SYSTEM_BACKUP
#define H_SYSTEM_BACKUP

#include <map>
#include <experimental/filesystem>

#include "backup.h"

class system_backup
{
public:
    int create_backup(const std::string& holder_file, const std::string& holder_backup)
    {
        _backups[_id_backup] = backup(holder_file, holder_backup);

        return _id_backup++;
    }

    void create_restore_point_base(int id)
    {
        _backups[id].create_restore_point_base();
    }

private:
    std::map<int, backup> _backups;
    static int _id_backup;
};

int system_backup::_id_backup = 0;

#endif