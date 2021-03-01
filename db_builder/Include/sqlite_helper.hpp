#pragma once
#include <sqlite3.h>
#include <string>
#include <memory>

struct sqlite_deleter {
  void operator()(sqlite3*  ptr) { if (ptr) sqlite3_close(ptr); }
};
using unique_sqlite3  = std::unique_ptr<sqlite3,  sqlite_deleter>;
// TODO: Consider applying above hack, for sqlite_stmt
/* using unique_sqlite3_stmt  = std::unique_ptr<sqlite3,  sqlite_deleter>; */ 

unique_sqlite3 open_db(const char db_name[]);
void throwSqliteException(unique_sqlite3& db, const std::string& errMsgPrefix, char* errMsgSuffix);
void throwSqliteException(unique_sqlite3& db, const std::string& errMsgPrefix);
