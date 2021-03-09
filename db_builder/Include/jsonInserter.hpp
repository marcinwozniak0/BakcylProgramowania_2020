#pragma once
#include <json/json.h>
#include "sqlite_helper.hpp"
#include <string>

void fillTableWithArrOfDicts(unique_sqlite3& db, const char table_name[], Json::Value arrOfDicts);
// Iterates over json array of objects (we use dict as synonym) and inserts corresponing fields to table
// If there is no corresponding field - inserts NULL
// Example:
// We have table foobar with columns: foo, bar, foof
// We pass json: [{"foo": "chuj", "bar": "dupa"}, {"foo": "chuj", "foof: "dupa"}]
// table after filling:
// | foo  | bar  |foof // headers
// |"chuj"|"dupa"|NULL
// |"chuj"| NULL |"dupa"
