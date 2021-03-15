#pragma once
#include <memory>
#include <sqlite3.h>
#include <string>
#include <vector>


struct sqlite_deleter {
  void operator()(sqlite3*  ptr) { if (ptr) sqlite3_close(ptr); }
};
using unique_sqlite3 = std::unique_ptr<sqlite3, sqlite_deleter>;
// TODO: Consider applying above hack, for sqlite_stmt
/* using unique_sqlite3_stmt  = std::unique_ptr<sqlite3,  sqlite_deleter>; */

unique_sqlite3 open_db(const char db_name[]);
sqlite3_stmt* prepare_stmt(unique_sqlite3& db, const char query[]);
void execDumbStmt(unique_sqlite3& db, sqlite3_stmt* stmt);
// This is for dumb, not returning statements (eg. insert)

const std::vector<std::string> getColumnNames(unique_sqlite3& db, const char tableName[]);
sqlite3_stmt* prepareInsertStatement(unique_sqlite3& db, const char table_name[], int colCount);
// SQLi-insecure itself. Caller should check if getColumnNames() (SQLi-safe method) returns any columns
