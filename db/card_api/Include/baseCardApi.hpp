#pragma once
#include "sqlite_helper.hpp"
#include <optional>
#include <string>
#include <vector>

namespace CardApi
{
struct Set
{
    std::string name;
    std::string abbreviation;
    // TODO: store info where icon is stored
};

struct Region
{
    std::string name;
    std::string abbreviation;
    // TODO: store info where icon is stored
    bool operator==(const Region& other) const{return (name == other.name);}
};

struct Rarity
{
    std::string name;
};

struct SpellSpeed
{
    std::string name;
};

// get all X. Could be useful for populating UI
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

    Set set;
    Region region;
    Rarity rarity;
    SpellSpeed spellSpeed;

    bool operator==(const Card& other) const{return (cardCode == other.cardCode);}
    // TODO: store info where icon is stored
    bool operator<(const Card& other) const{return (name < other.name);}
};

std::optional<Card> getCardById(SqliteHelper::unique_sqlite3& db, const std::string& cardCode);
// exact match
} // namespace CardApi
