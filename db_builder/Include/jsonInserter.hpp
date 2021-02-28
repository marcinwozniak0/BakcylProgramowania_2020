#pragma once
#include <json/json.h>
#include <sqlite3.h>
#include <string>

void fillTableWithArrOfDicts(sqlite3* db, const char table_name[], Json::Value arrOfDicts);
// Iterates over json array of objects (we use dict as synonym) and inserts corresponing fields to table
// If there is no corresponding field - inserts NULL
// Example:
// We have table foobar with columns: foo, bar, foof
// We pass json: [{"foo": "chuj", "bar": "dupa"}, {"foo": "chuj", "foof: "dupa"}]
// table after filling:
// | foo  | bar  |foof // headers
// |"chuj"|"dupa"|NULL
// |"chuj"| NULL |"dupa"
