#include "baseCardApi.hpp"

namespace CardApi
{
std::vector<Set> getAllSets(unique_sqlite3& db)
{
    const char query[] = "SELECT name, iconAbsolutePath FROM sets";
    auto stmt = prepare_stmt(db, query);
    std::vector<Set> sets;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        Set set;
        set.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        /* set.iconURL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); */
        sets.push_back(set);
    }
    return sets;
    sqlite3_finalize(stmt);
}

std::vector<Region> getAllRegions(unique_sqlite3& db)
{
    const char query[] = "SELECT name, abbreviation, iconAbsolutePath FROM regions";
    auto stmt = prepare_stmt(db, query);
    std::vector<Region> regions;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        Region region;
        region.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        region.abbreviation = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        /* region.iconURL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); */
        regions.push_back(region);
    }
    return regions;
    sqlite3_finalize(stmt);
}

std::vector<Rarity> getAllRarities(unique_sqlite3& db)
{
    const char query[] = "SELECT name FROM rarities";
    auto stmt = prepare_stmt(db, query);
    std::vector<Rarity> rarities;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        Rarity rarity;
        rarity.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        rarities.push_back(rarity);
    }
    return rarities;
    sqlite3_finalize(stmt);
}

std::vector<SpellSpeed> getAllSpellSpeeds(unique_sqlite3& db)
{
    const char query[] = "SELECT name FROM spellSpeeds";
    auto stmt = prepare_stmt(db, query);
    std::vector<SpellSpeed> spellSpeeds;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        SpellSpeed spellSpeed;
        spellSpeed.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        spellSpeeds.push_back(spellSpeed);
    }
    return spellSpeeds;
    sqlite3_finalize(stmt);
}
}
