#pragma once
#include "sqlite_helper.hpp"
#include <optional>
#include <string>
#include <vector>

struct Set
{
    std::string name;
    // TODO: store info where icon is stored
};

struct Region
{
    std::string name;
    std::string abbreviation;
    // TODO: store info where icon is stored
};

struct Rarity
{
    std::string name;
};

struct SpellSpeed
{
    std::string name;
};

std::vector<Set> getAllSets(SqliteHelper::unique_sqlite3& db);
std::vector<Region> getAllRegions(SqliteHelper::unique_sqlite3& db);
std::vector<Rarity> getAllRarities(SqliteHelper::unique_sqlite3& db);
std::vector<SpellSpeed> getAllSpellSpeeds(SqliteHelper::unique_sqlite3& db);

struct Card
{
    std::string cardCode;
    std::string name;
    int attack;
    int cost;
    int health;
    std::string artistName;
    bool isCollectible;
    std::string description;
    std::string levelupDescription;
    std::string flavorText;
    std::string supertype;
    std::string type;
    // TODO: store sets, regions etc. to which card belongs
    /* Set set; */
    /* Region region; */
    /* Rarity rarity; */
    /* SpellSpeed spellSpeed; */
    // TODO: store info where icon is stored
};
