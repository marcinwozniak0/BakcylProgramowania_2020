#pragma once
#include <sqlite3.h>
#include <string>

sqlite3* open_db(const char db_name[]);
void throwSqliteException(sqlite3* db, const std::string& errMsgPrefix, char* errMsgSuffix);
void throwSqliteException(sqlite3* db, const std::string& errMsgPrefix);
