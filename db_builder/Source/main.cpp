#include "jsonInserter.hpp"
#include "sqlite_helper.hpp"
#include "filedownloader.h"
#include <cstring>
#include <fstream>
#include <json/json.h>
#include <sqlite3.h>

void fillGlobals(unique_sqlite3& db, const Json::Value& json);
void fillCards(unique_sqlite3& db, const Json::Value& json);
void createTables(unique_sqlite3& db);
std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it);
void fillSet(unique_sqlite3& db, const Json::Value& set);
void fillAssoc(unique_sqlite3& db, const Json::Value& cards, const std::string& table_name, const std::string& arrName);
void fillAssets(unique_sqlite3& db, const Json::Value& cards);

static std::string directoryPath_ = "./data";

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
        file.close();
        
        fd::FileDownloader downloader;                              
        downloader.createDirectory(directoryPath_);

        std::vector <std::string> links_;
        links_.push_back(download_url);
        std::vector <std::string> fileNames_;
        fileNames_.push_back(filename);
        downloader.addLinks(links_, fileNames_, links_.size());
        downloader.download(false);
        
        std::string filename_ = directoryPath_ + "/" + filename;
        file.open(filename_);
    }
    file >> json;
    return json;
}

int main()
{
    unique_sqlite3 db = open_db("database.sql");
    sqlite3_exec(db.get(), "BEGIN TRANSACTION;", NULL, NULL, NULL);
    createTables(db);

    fd::FileDownloader downloader;  
    downloader.addDirectoryPath(directoryPath_);
    
    // Downloading Zips with images
    // adding info for downloading (links, file names)
    std::vector <std::string> links_;
    links_.push_back("https://dd.b.pvp.net/latest/set1-lite-en_us.zip");
    links_.push_back("https://dd.b.pvp.net/latest/set2-lite-en_us.zip");
    links_.push_back("https://dd.b.pvp.net/latest/set3-lite-en_us.zip");
    links_.push_back("https://dd.b.pvp.net/latest/set4-lite-en_us.zip");
    
    std::vector <std::string> fileNames_;
    fileNames_.push_back("set1-lite-en_us.zip");
    fileNames_.push_back("set2-lite-en_us.zip");
    fileNames_.push_back("set3-lite-en_us.zip");
    fileNames_.push_back("set4-lite-en_us.zip");
    
    downloader.addLinks(links_, fileNames_, links_.size());
    
    downloader.download(true);
    
    
    // temporary ugly shit. We are going to abadon it for sake of auto downloading
    Json::Value globalsJson =
        getJsonFromFile("globals-en_us.json", "https://dd.b.pvp.net/latest/core/en_us/data/globals-en_us.json");
    fillGlobals(db, globalsJson);
    for (char i = '1'; i < '5'; ++i)
    {
        const auto setName = std::string("set") + i;
        const auto fileName = setName + "-en_us.json";
        auto url = "https://dd.b.pvp.net/latest/" + setName + "/en_us/data/" + fileName;
        Json::Value setJson = getJsonFromFile(fileName, url);
        fillSet(db, setJson);
    }

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

void fillSet(unique_sqlite3& db, const Json::Value& set)
{
    fillTableWithArrOfDicts(db, "cards", set);
    fillAssoc(db, set, "cardSubtypes", "subtypes");
    fillAssoc(db, set, "associatedCards", "associatedCardRefs");
    fillAssoc(db, set, "cardKeywords", "keywordRefs");
    fillAssets(db, set);
}

void fillAssoc(unique_sqlite3& db, const Json::Value& cards, const std::string& table_name, const std::string& arrName)
{
    sqlite3_stmt* stmt = prepareInsertStatement(db, table_name.c_str(), 2);
    for (const auto& card : cards)
    {
        sqlite3_bind_text(stmt, 1, card["cardCode"].asCString(), -1, NULL);
        for (const auto& elem : card[arrName])
        {
            sqlite3_bind_text(stmt, 2, elem.asCString(), -1, NULL);
            execDumbStmt(db, stmt);
        }
    }
    sqlite3_finalize(stmt);
}

void fillAssets(unique_sqlite3& db, const Json::Value& cards)
{
    sqlite3_stmt* stmt = prepareInsertStatement(db, "cardAssets", 3);
    for (const auto& card : cards)
    {
        sqlite3_bind_text(stmt, 1, card["cardCode"].asCString(), -1, NULL);
        for (const auto& asset : card["assets"])
        {
            sqlite3_bind_text(stmt, 2, asset["gameAbsolutePath"].asCString(), -1, NULL);
            sqlite3_bind_text(stmt, 3, asset["fullAbsolutePath"].asCString(), -1, NULL);
            execDumbStmt(db, stmt);
        }
    }
}

std::string getJsonMemberNameWithoutNuls(Json::ValueIteratorBase it)
{
    // Jsoncpp tries to "be liberal in what it accepts" and allows for not-escaped embedded NUL characters in json
    // string. This is not allowed in valid json, but could be useful for storing BLOBs. However sometimes you need just
    // null-terminated string which of course is unable to embed NULs Jsoncpp has deprecated memberName() method, which
    // returns CString and just quietly cuts part after first NUL Instead of using deprecated, kinda unsafe method, we
    // fail fast at strings with embedded NULs
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
