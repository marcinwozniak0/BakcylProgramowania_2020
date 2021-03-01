#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include <fstream>
#include <json/json.h>
#include <sqlite3.h>

void fillDbWithRiotJson(unique_sqlite3& db, Json::Value json);
void createTables(unique_sqlite3& db);

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int main()
{
    unique_sqlite3 db = open_db("database.sql");
    createTables(db);
    std::ifstream input("globals-ru_ru.json");
    if (is_empty(input))
    {
        // ya ya. This sucks, but it is sufficient for this PoC
        throw std::runtime_error("There are no json in globals-ru_ru.json. Download it from "
              "https://dd.b.pvp.net/latest/core/ru_ru/data/globals-ru_ru.json");
    }
    Json::Value json;
    input >> json;
    fillDbWithRiotJson(db, json);
}

void createTables(unique_sqlite3& db)
{
    // I have doubts about formating
    constexpr char query[] = R"""(
    CREATE TABLE IF NOT EXISTS "vocabTerms" ("nameRef"	TEXT,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "keywords" ("nameRef"	TEXT,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "spellSpeeds" ("nameRef"	TEXT,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "sets" ("nameRef"	TEXT,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "regions" ("nameRef"	TEXT,"abbreviation"	TEXT,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "rarities" ("nameRef"	TEXT,"value"	INTEGER,PRIMARY KEY("nameRef"));
    CREATE TABLE IF NOT EXISTS "associatedCards" ("cardCode"	TEXT,"associatedCardCode"	TEXT,FOREIGN KEY("associatedCardCode") REFERENCES "cards"("cardCode"),FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode"));
    CREATE TABLE IF NOT EXISTS "languages" ("langCode"	TEXT,PRIMARY KEY("langCode"));
    CREATE TABLE IF NOT EXISTS "keywordsTranslations" ("nameRef"	TEXT,"langCode"	TEXT,"description"	TEXT,"name"	TEXT,FOREIGN KEY("nameRef") REFERENCES "keywords"("nameRef"),PRIMARY KEY("nameRef","langCode"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"));
    CREATE TABLE IF NOT EXISTS "vocabTermsTranslations" ("nameRef"	TEXT,"langCode"	TEXT,"name"	TEXT,"description"	TEXT,PRIMARY KEY("nameRef","langCode"),FOREIGN KEY("nameRef") REFERENCES "vocabTerms"("nameRef"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"));
    CREATE TABLE IF NOT EXISTS "regionsTranslations" ("nameRef"	TEXT,"langCode"	TEXT,"iconAbsolutePath"	TEXT,"name"	TEXT,FOREIGN KEY("nameRef") REFERENCES "regions"("nameRef"),PRIMARY KEY("nameRef","langCode"));
    CREATE TABLE IF NOT EXISTS "cards" ("cardCode"	TEXT UNIQUE,"regionRef"	TEXT,"attack"	INTEGER,"cost"	INTEGER,"health"	INTEGER,"artistName"	TEXT,"spellSpeedRef"	TEXT,"rarityRef"	TEXT,"collectible"	INTEGER,"set"	TEXT,FOREIGN KEY("set") REFERENCES "sets"("nameRef"),FOREIGN KEY("rarityRef") REFERENCES "rarities"("nameRef"),FOREIGN KEY("spellSpeedRef") REFERENCES "spellSpeeds"("nameRef"),PRIMARY KEY("cardCode"),FOREIGN KEY("regionRef") REFERENCES "regions"("nameRef"));
    CREATE TABLE IF NOT EXISTS "cardKeywords" ("cardCode"	TEXT,"keywordRef"	INTEGER,FOREIGN KEY("keywordRef") REFERENCES "keywords"("nameRef"),FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode"));
    CREATE TABLE IF NOT EXISTS "cardAssetsTranslations" ("cardCode"	TEXT,"gameAbsolutePath"	TEXT,"fullAbsolutePath"	TEXT,FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode"));
    CREATE TABLE IF NOT EXISTS "setsTranslations" ("langCode"	TEXT,"nameRef"	TEXT,"iconAbsolutePath"	TEXT,"name"	TEXT,PRIMARY KEY("langCode","nameRef"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"),FOREIGN KEY("nameRef") REFERENCES "sets"("nameRef"));
    CREATE TABLE IF NOT EXISTS "raritiesTranslations" ("langCode"	TEXT,"nameRef"	TEXT,"name"	TEXT,PRIMARY KEY("langCode","nameRef"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"),FOREIGN KEY("nameRef") REFERENCES "rarities"("nameRef"));
    CREATE TABLE IF NOT EXISTS "cardTranslations" ("cardCode"	TEXT,"langCode"	TEXT,"descriptionRaw"	TEXT,"levelupDescriptionRaw"	TEXT,"flavorText"	TEXT,"name"	TEXT,"supertype"	TEXT,"type"	TEXT,PRIMARY KEY("cardCode","langCode"),FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"));
    CREATE TABLE IF NOT EXISTS "cardSubtypesTranslation" ("cardCode"	TEXT,"langCode"	TEXT,"subtype"	TEXT,FOREIGN KEY("cardCode") REFERENCES "cards"("cardCode"),FOREIGN KEY("langCode") REFERENCES "languages"("langCode"));
    CREATE TABLE IF NOT EXISTS "spellSpeedsTranslations" ("nameRef"	TEXT,"langCode"	TEXT,"name"	TEXT,FOREIGN KEY("langCode") REFERENCES "languages"("langCode"),PRIMARY KEY("nameRef","langCode"),FOREIGN KEY("nameRef") REFERENCES "spellSpeeds"("nameRef"));
    )""";
    char* errMsg = NULL;
    int result_code = sqlite3_exec(db.get(), query, NULL, NULL, &errMsg);
    if (result_code != SQLITE_OK)
    {
        throwSqliteException(db, "SQL Error: ", errMsg);
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

void fillDbWithRiotJson(unique_sqlite3& db, Json::Value json)
// TODO: it should add info about lang, to database
{
    for (auto field = json.begin(); field != json.end(); ++field)
    {
        auto langAgnosticTable = getJsonMemberNameWithoutNuls(field);
        auto langDependentTable = langAgnosticTable + "Translations";
        auto& value = *field;
        fillTableWithArrOfDicts(db, langAgnosticTable.c_str(), value); 
        fillTableWithArrOfDicts(db, langDependentTable.c_str(), value); 
    }
}
