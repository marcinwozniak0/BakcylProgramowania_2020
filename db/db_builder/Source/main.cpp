#include "iostream"
#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include <cstring>
#include <fstream>
#include <json/json.h>
#include <sqlite3.h>

void fillGlobals(SqliteHelper::unique_sqlite3& db, const Json::Value& json);
void fillCards(SqliteHelper::unique_sqlite3& db, const Json::Value& json);
void createTables(SqliteHelper::unique_sqlite3& db);
std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it);
void fillSet(SqliteHelper::unique_sqlite3& db, const Json::Value& set);
void fillAssoc(SqliteHelper::unique_sqlite3& db, const Json::Value& cards, const std::string& table_name,
               const std::string& arrName);
void fillAssets(SqliteHelper::unique_sqlite3& db, const Json::Value& cards);

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

Json::Value getJsonFromFile(const std::string& filename, const std::string& download_url)
{
    Json::Value json;
    std::ifstream file(filename);
    if (is_empty(file))
    {
        // ya ya. This sucks, but it is sufficient for this PoC
        // Besides something tells me that it shouldn't be exception
        throw std::runtime_error(
            std::string("There are no json in " + filename + " Download it from " + std::string(download_url)));
    }
    file >> json;
    return json;
}

int main()
{
    SqliteHelper::unique_sqlite3 db = SqliteHelper::open_db("database.sql");
    sqlite3_exec(db.get(), "BEGIN TRANSACTION;", NULL, NULL, NULL);
    createTables(db);

    // temporary ugly shit. We are going to abadon it for sake of auto downloading
    Json::Value globalsJson =
        getJsonFromFile("globals-pl_pl.json", "https://dd.b.pvp.net/latest/core/pl_pl/data/globals-pl_pl.json");
    fillGlobals(db, globalsJson);
    for (char i = '1'; i < '5'; ++i)
    {
        const auto setName = std::string("set") + i;
        const auto fileName = setName + "-pl_pl.json";
        auto url = "https://dd.b.pvp.net/latest/" + setName + "/pl_pl/data/" + fileName;
        Json::Value setJson = getJsonFromFile(fileName, url);
        fillSet(db, setJson);
    }

    sqlite3_exec(db.get(), "END TRANSACTION;", NULL, NULL, NULL);
}

void fillGlobals(SqliteHelper::unique_sqlite3& db, const Json::Value& json)
{
    for (auto field = json.begin(); field != json.end(); ++field)
    {
        auto tableName = getJsonMemberNameWithoutNuls(field);
        auto& value = *field;
        fillTableWithArrOfDicts(db, tableName.c_str(), value);
    }
}

void fillSet(SqliteHelper::unique_sqlite3& db, const Json::Value& set)
{
    fillTableWithArrOfDicts(db, "cards", set);
    fillAssoc(db, set, "cardSubtypes", "subtypes");
    fillAssoc(db, set, "associatedCards", "associatedCardRefs");
    fillAssoc(db, set, "cardKeywords", "keywordRefs");
    fillAssets(db, set);
}

void fillAssoc(SqliteHelper::unique_sqlite3& db, const Json::Value& cards, const std::string& table_name,
               const std::string& arrName)
{
    auto stmt = prepareInsertStatement(db, table_name.c_str(), 2);
    for (const auto& card : cards)
    {
        sqlite3_bind_text(stmt.get(), 1, card["cardCode"].asCString(), -1, NULL);
        for (const auto& elem : card[arrName])
        {
            sqlite3_bind_text(stmt.get(), 2, elem.asCString(), -1, NULL);
            execDumbStmt(db, stmt);
        }
    }
}

void fillAssets(SqliteHelper::unique_sqlite3& db, const Json::Value& cards)
{
    auto stmt = prepareInsertStatement(db, "cardAssets", 3);
    for (const auto& card : cards)
    {
        sqlite3_bind_text(stmt.get(), 1, card["cardCode"].asCString(), -1, NULL);
        for (const auto& asset : card["assets"])
        {
            sqlite3_bind_text(stmt.get(), 2, asset["gameAbsolutePath"].asCString(), -1, NULL);
            sqlite3_bind_text(stmt.get(), 3, asset["fullAbsolutePath"].asCString(), -1, NULL);
            execDumbStmt(db, stmt);
        }
    }
}

std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it)
{
    // Jsoncpp tries to "be liberal in what it accepts" and allows for not-escaped embedded NUL characters in json
    // string. This is not allowed in valid json, but could be useful for storing BLOBs. However sometimes you need just
    // null-terminated string which of course is unable to embed NULs. Jsoncpp has deprecated memberName() method, which
    // returns CString and just quietly cuts part after first NUL. Instead of using deprecated, kinda unsafe method, we
    // fail fast at strings with embedded NULs
    auto memberName = it.name();
    if (memberName.size() != std::strlen(memberName.c_str()))
    {
        throw std::invalid_argument("Json string must not have embedded NUL characters");
    }
    return memberName;
}

void createTables(SqliteHelper::unique_sqlite3& db)
{
    // I have doubts about formating
    constexpr char query[] = R"""(
    CREATE TABLE IF NOT EXISTS "keywords"(
      "nameRef"	TEXT,
      "description"	TEXT, -- localized
      "name"	TEXT, -- localized
      PRIMARY KEY("nameRef")
    );
    CREATE TABLE IF NOT EXISTS "spellSpeeds"(
      "nameRef"	TEXT,
      "name"	TEXT, -- localized
      PRIMARY KEY("nameRef")
     );
    CREATE TABLE IF NOT EXISTS "sets"(
      "nameRef"	TEXT,
      "iconAbsolutePath"	TEXT, -- localized
      "name"	TEXT, -- localized
      PRIMARY KEY("nameRef")
     );
    CREATE TABLE IF NOT EXISTS "regions"(
      "nameRef"	TEXT,
      "abbreviation"	TEXT, -- probably not localized
      "iconAbsolutePath" TEXT, -- localized
      "name"	TEXT, -- localized
      PRIMARY KEY("nameRef")
    );
    CREATE TABLE IF NOT EXISTS "rarities"(
      "nameRef"	TEXT,
      "name" TEXT, -- localized
      PRIMARY KEY("nameRef")
     );
    CREATE TABLE IF NOT EXISTS "associatedCards"(
      "cardCode"	TEXT,
      "associatedCardCode"	TEXT,
      FOREIGN KEY("associatedCardCode") REFERENCES "cards"("cardCode"),
      FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode")
    );
    CREATE TABLE IF NOT EXISTS "cards"(
      "cardCode"	TEXT UNIQUE,
      "regionRef"	TEXT,
      "attack"	INTEGER,
      "cost"	INTEGER,
      "health"	INTEGER,
      "artistName"	TEXT,
      "spellSpeedRef"	TEXT,
      "rarityRef"	TEXT,
      "collectible"	INTEGER,
      "set"	TEXT,
      "descriptionRaw"	TEXT, -- localized
      "levelupDescriptionRaw"	TEXT, -- localized
      "flavorText"	TEXT, -- localized
      "name"	TEXT, -- localized
      "supertype"	TEXT, -- localized
      "type"	TEXT, -- localized
      FOREIGN KEY("set") REFERENCES "sets"("nameRef"),
      FOREIGN KEY("rarityRef") REFERENCES "rarities"("nameRef"),
      FOREIGN KEY("spellSpeedRef") REFERENCES "spellSpeeds"("nameRef"),
      PRIMARY KEY("cardCode"),
      FOREIGN KEY("regionRef") REFERENCES "regions"("nameRef")
    );
    CREATE TABLE IF NOT EXISTS "cardKeywords"(
      "cardCode"	TEXT,
      "keywordRef"	INTEGER,
      FOREIGN KEY("keywordRef") REFERENCES "keywords"("nameRef"),
      FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode")
    );
    CREATE TABLE IF NOT EXISTS "cardAssets"(
      "cardCode"	TEXT,
      "gameAbsolutePath"	TEXT, -- localization dependent
      "fullAbsolutePath"	TEXT, -- localization dependent
      FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode")
    );
    CREATE TABLE IF NOT EXISTS "cardSubtypes"(
      "cardCode"	TEXT,
      "subtype"	TEXT, -- localization dependent
      FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode")
    );
    )""";
    int result_code = sqlite3_exec(db.get(), query, NULL, NULL, NULL);
    if (result_code != SQLITE_OK)
    {
        throw std::runtime_error(std::string("SQL Error: ") + sqlite3_errmsg(db.get()));
    }
}
