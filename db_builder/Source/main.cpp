#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include <fstream>
#include <json/json.h>
#include <sqlite3.h>
#include <cstring>


void fillGlobals(unique_sqlite3& db, const Json::Value& json);
void fillCards(unique_sqlite3& db, const Json::Value& json);
void createTables(unique_sqlite3& db);
std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it);

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

Json::Value getJsonFromFile(const char filename[], const char download_url[])
{
    Json::Value json;
    std::ifstream file(filename);
    if (is_empty(file))
    {
        // ya ya. This sucks, but it is sufficient for this PoC
        throw std::runtime_error(std::string("There are no json in globals-ru_ru.json. Download it from " + std::string(download_url)));
    }
    file >> json;
    return json;
}

int main()
{
    unique_sqlite3 db = open_db("database.sql");
    sqlite3_exec(db.get(), "BEGIN TRANSACTION;", NULL, NULL, NULL);
    createTables(db);

    Json::Value json;
    json = getJsonFromFile("globals-ru_ru.json", "https://dd.b.pvp.net/latest/core/ru_ru/data/globals-ru_ru.json");
    fillGlobals(db, json);
    json = getJsonFromFile("set1-ru_ru.json", "https://dd.b.pvp.net/latest/core/ru_ru/data/globals-ru_ru.json");
    fillTableWithArrOfDicts(db, "cards", json); 

    sqlite3_exec(db.get(), "END TRANSACTION;", NULL, NULL, NULL);
}

void fillGlobals(unique_sqlite3& db, const Json::Value& json)
{
    for (auto field = json.begin(); field != json.end(); ++field)
    {
        auto tableName = getJsonMemberNameWithoutNuls(field);
        auto& value = *field;
        fillTableWithArrOfDicts(db, tableName.c_str(), value); 
    }
}

std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it)
{
    // Jsoncpp tries to "be liberal in what it accepts" and allows for not-escaped embedded NUL characters in json string.
    // This is not allowed in valid json, but could be useful for storing BLOBs.
    // However sometimes you need just null-terminated string which of course is unable to embed NULs
    // Jsoncpp has deprecated memberName() method, which returns CString and just quietly cuts part after first NUL
    // Instead of using deprecated, kinda unsafe method, we fail fast at strings with embedded NULs
    auto memberName = it.name();
    if (memberName.size() != std::strlen(memberName.c_str()))
    {
        throw std::runtime_error("Json string must not have embedded NUL characters");
    }
    return memberName;
}

void createTables(unique_sqlite3& db)
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
