#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include <iostream>

namespace
{
const std::vector<std::string> getColumnNames(unique_sqlite3& db, const char tableName[]);
sqlite3_stmt* prepareInsertStatement(unique_sqlite3& db, const char table_name[], int colCount); // SQLi-insecure itself.
// Caller should check if getColumnNames() (SQLi-safe method) returns any columns
void bindJsonDictToInsertStatement(sqlite3_stmt* stmt, const std::vector<std::string>& colNames,
                                   const Json::Value& json);
} // namespace

void fillTableWithArrOfDicts(unique_sqlite3& db, const char table_name[], Json::Value json)
{
    const auto colNames = getColumnNames(db, table_name);
    if(colNames.size() == 0)
    {
        std::cout << "Ommiting not existing table \"" << table_name << "\"\n";
        return;
    }
    sqlite3_stmt* stmt = prepareInsertStatement(db, table_name, colNames.size());
    for (auto dict = json.begin(); dict != json.end(); ++dict)
    {
        bindJsonDictToInsertStatement(stmt, colNames, *dict);
        int rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE)
        {
            sqlite3_finalize(stmt);
            throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
        }
        sqlite3_reset(stmt);
        sqlite3_clear_bindings(stmt);
    }
    sqlite3_finalize(stmt);
}

namespace
{
const std::vector<std::string> getColumnNames(unique_sqlite3& db, const char tableName[])
{
    sqlite3_stmt* stmt;
    std::vector<std::string> output;
    int rc = sqlite3_prepare_v2(db.get(), "SELECT name FROM pragma_table_info(@table)", -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, "@table"), tableName, -1, NULL);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        std::string colName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        output.push_back(colName);
    }
    sqlite3_finalize(stmt);
    if (rc != SQLITE_DONE)
    {
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    return output;
}

sqlite3_stmt* prepareInsertStatement(unique_sqlite3& db, const char table_name[], int colCount)
{
    // Unfortunately sqlite_bind_param() doesn't work for table identifiers.
    // We must resort to binding table_name using dumb string concat.
    // This is generaly bad idea mainly because of SQL injection vurnelibity.
    // However caller could ensure safety by passing valid colCount (at example from getColumnNames().size(), which is SQLi-safe method
    // colCount == 0 means that table doesn't exist so we don't inject it name
    // AFAIK this should be sufficient countermeasure. Prove me wrong.
    // Also. In case of this parser, SQL injection isn't that big deal
    // We are storing data from only one entity. He doesn't need SQLi to read or malform it :P
    std::string query = std::string("INSERT INTO ") + table_name + " VALUES(";
    for (int i = 0; i < colCount; ++i)
    {
        if (i != 0)
        {
            query += ',';
        }
        query += '?';
    }
    query += ')';

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db.get(), query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    return stmt;
}

void bindJsonDictToInsertStatement(sqlite3_stmt* stmt, const std::vector<std::string>& colNames,
                                   const Json::Value& dict)
{
    for (size_t i = 0; i < colNames.size(); ++i)
    {
        std::string colName = colNames[i];
        const auto val = dict.find(&colName.front(), &colName.back() + 1);
        const int paramIdx = i + 1; // sqlite3_bind() starts indexing from 1
        if (val == NULL or val->isNull())
        {
            sqlite3_bind_null(stmt, paramIdx);
        }
        else if (val->isString())
        {
            sqlite3_bind_text(stmt, paramIdx, val->asCString(), -1, NULL);
        }
        else if (val->isInt() or val->isBool())
        {
            sqlite3_bind_int(stmt, paramIdx, val->asInt());
        }
        else if (val->isDouble())
        {
            sqlite3_bind_double(stmt, paramIdx, val->asDouble());
        }
        else
        {
            sqlite3_finalize(stmt);
            throw std::runtime_error("Unable to bind value to insert statement"); // poor msg. TODO: improve this
        }
    }
}
} // namespace
