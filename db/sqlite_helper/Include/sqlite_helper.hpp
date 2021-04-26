#pragma once
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>

namespace SqliteHelper
{
struct sqlite_deleter
{
    void operator()(sqlite3* ptr)
    {
        if (ptr)
            sqlite3_close(ptr);
    }
    void operator()(sqlite3_stmt* ptr)
    {
        if (ptr)
            sqlite3_finalize(ptr);
    }
};
using unique_sqlite3 = std::unique_ptr<sqlite3, sqlite_deleter>;
using unique_stmt = std::unique_ptr<sqlite3_stmt, sqlite_deleter>;

unique_sqlite3 open_db(const char db_name[]);
unique_stmt prepare_stmt(unique_sqlite3& db, const char query[]);
void execDumbStmt(unique_sqlite3& db, const unique_stmt& stmt);
// This is for dumb, not returning statements (eg. insert)

const std::vector<std::string> getColumnNames(unique_sqlite3& db, const char tableName[]);
unique_stmt prepareInsertStatement(unique_sqlite3& db, const char table_name[], int colCount);
// SQLi-insecure itself. Caller should check if getColumnNames() (SQLi-safe method) returns any columns

std::string buildPlaceholdersList(int elemCount);
// produces string with list of unnamed placeholders in paranthes
// elemCount == 0 -> "()"
// elemCount == 1 -> "(?)"
// elemCount == 2 -> "(?, ?)"
// ...
}
