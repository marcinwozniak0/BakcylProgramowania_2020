#include "sqlite_helper.hpp"
#include <stdexcept>

sqlite3* open_db(const char db_name[])
{
    sqlite3* db; // Maybe I should wrap this into simple RAII handle or smart pointer?
    int resultCode = sqlite3_open(db_name, &db);
    if (resultCode != SQLITE_OK)
    {
        throwSqliteException(db, "Can't open database: ");
    }
    return db;
}

void throwSqliteException(sqlite3* db, const std::string& errMsgPrefix, char* errMsgSuffix)
{
    std::string errMsg = errMsgPrefix + errMsgSuffix;
    sqlite3_free(errMsgSuffix);
    sqlite3_close(db); // I have doubts with this one. Mixing exceptions with hand memory managment is nightmare.
    throw std::runtime_error(errMsg);
}

void throwSqliteException(sqlite3* db, const std::string& errMsgPrefix)
{
    std::string errMsg = errMsgPrefix + sqlite3_errmsg(db);
    sqlite3_close(db); // I have doubts with this one. Mixing exceptions with hand memory managment is nightmare.
    throw std::runtime_error(errMsg);
}
