#include "sqlite_helper.hpp"
#include <stdexcept>
#include <memory>

unique_sqlite3 open_db(const char db_name[])
{
    sqlite3* tmp;
    int resultCode = sqlite3_open(db_name, &tmp);
    if (resultCode != SQLITE_OK)
    {
        std::string errMsg = std::string("Can't open database: ") + sqlite3_errmsg(tmp);
        throw std::runtime_error(errMsg);
    }
    return unique_sqlite3(tmp);
}
