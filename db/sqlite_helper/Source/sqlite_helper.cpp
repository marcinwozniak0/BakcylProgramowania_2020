#include "sqlite_helper.hpp"
#include <memory>
#include <stdexcept>

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

unique_sqlite3_stmt prepare_stmt(unique_sqlite3& db, const char query[])
{
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db.get(), query, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        sqlite3_finalize(stmt);
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    return unique_sqlite3_stmt(stmt);
}

void execDumbStmt(unique_sqlite3& db, const unique_sqlite3_stmt& stmt)
{
    int rc = sqlite3_step(stmt.get());
    if (rc != SQLITE_DONE)
    {
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    sqlite3_reset(stmt.get());
}

const std::vector<std::string> getColumnNames(unique_sqlite3& db, const char tableName[])
{
    auto stmt = prepare_stmt(db, "SELECT name FROM pragma_table_info(@table)");
    sqlite3_bind_text(stmt.get(), sqlite3_bind_parameter_index(stmt.get(), "@table"), tableName, -1, NULL);
    std::vector<std::string> output;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        std::string colName = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        output.push_back(colName);
    }
    if (rc != SQLITE_DONE)
    {
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
    return output;
}

std::string buildPlaceholdersList(int elemCount)
{
    std::string query = "(";
    query.reserve(2 * elemCount + 1); // premature optimization :P
    for (int i = 0; i < elemCount; ++i)
    {
        if (i != 0)
        {
            query += ',';
        }
        query += '?';
    }
    query += ')';
    return query;
}


unique_sqlite3_stmt prepareInsertStatement(unique_sqlite3& db, const char table_name[], int colCount)
{
    // Unfortunately sqlite_bind_param() doesn't work for table identifiers.
    // We must resort to binding table_name using dumb string concat.
    // This is generaly bad idea mainly because of SQL injection vurnelibity.
    // However caller could ensure safety by passing valid colCount (at example from getColumnNames().size(), which is
    // SQLi-safe method colCount == 0 means that table doesn't exist so we don't inject it name AFAIK this should be
    // sufficient countermeasure. Prove me wrong. Also. In case of this parser, SQL injection isn't that big deal We are
    // storing data from only one entity. He doesn't need SQLi to read or malform it :P
    std::string query = std::string("INSERT INTO ") + table_name + " VALUES";
    query += buildPlaceholdersList(colCount);
    
    auto stmt = prepare_stmt(db, query.c_str());
    return stmt;
}
