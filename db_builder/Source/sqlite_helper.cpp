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

sqlite3_stmt* prepare_stmt(unique_sqlite3& db, const char query[])
{
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db.get(), query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    return stmt;
}
void execDumbStmt(unique_sqlite3& db, sqlite3_stmt* stmt)
{
    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    sqlite3_reset(stmt);
}
