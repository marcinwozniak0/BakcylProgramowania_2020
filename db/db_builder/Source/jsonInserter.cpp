#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include <iostream>

namespace
{
void bindJsonDictToInsertStatement(SqliteHelper::unique_sqlite3_stmt& stmt, const std::vector<std::string>& colNames,
                                   const Json::Value& json);
} // namespace

void fillTableWithArrOfDicts(SqliteHelper::unique_sqlite3& db, const char table_name[], const Json::Value& json)
{
    const auto colNames = getColumnNames(db, table_name);
    if (colNames.size() == 0)
    {
        std::cout << "Ommiting not existing table \"" << table_name << "\"\n";
        return;
    }
    auto stmt = prepareInsertStatement(db, table_name, colNames.size());
    for (const auto& dict : json)
    {
        bindJsonDictToInsertStatement(stmt, colNames, dict);
        execDumbStmt(db, stmt);
    }
}

namespace
{
void bindJsonDictToInsertStatement(SqliteHelper::unique_sqlite3_stmt& stmt, const std::vector<std::string>& colNames,
                                   const Json::Value& dict)
{
    for (size_t i = 0; i < colNames.size(); ++i)
    {
        std::string colName = colNames[i];
        const auto val = dict.find(&colName.front(), &colName.back() + 1);
        const int paramIdx = i + 1; // sqlite3_bind() starts indexing from 1
        if (val == NULL or val->isNull())
        {
            sqlite3_bind_null(stmt.get(), paramIdx);
        }
        else if (val->isString())
        {
            sqlite3_bind_text(stmt.get(), paramIdx, val->asCString(), -1, NULL);
        }
        else if (val->isInt() or val->isBool())
        {
            sqlite3_bind_int(stmt.get(), paramIdx, val->asInt());
        }
        else if (val->isDouble())
        {
            sqlite3_bind_double(stmt.get(), paramIdx, val->asDouble());
        }
        else
        {
            sqlite3_finalize(stmt.get());
            throw std::runtime_error("Unable to bind value to insert statement"); // poor msg. TODO: improve this
        }
    }
}
} // namespace
