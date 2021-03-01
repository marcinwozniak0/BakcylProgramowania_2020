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

void throwSqliteException(unique_sqlite3& db, const std::string& errMsgPrefix, char* errMsgSuffix)
{
    std::string errMsg = errMsgPrefix + errMsgSuffix;
    sqlite3_free(errMsgSuffix);
    throw std::runtime_error(errMsg);
}

void throwSqliteException(unique_sqlite3& db, const std::string& errMsgPrefix)
{
    std::string errMsg = errMsgPrefix + sqlite3_errmsg(db.get());
    throw std::runtime_error(errMsg);
}
