#include "baseCardApi.hpp"
#include "utilities.hpp"
#include <stdexcept>

namespace CardApi
{
std::vector<Set> getAllSets(SqliteHelper::unique_sqlite3& db)
{
    const char query[] = "SELECT name, nameRef FROM sets";
    auto stmt = prepare_stmt(db, query);
    std::vector<Set> sets;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        Set set;
        set.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        set.abbreviation = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
        /* set.iconURL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); */
        sets.push_back(set);
    }
    return sets;
}

std::vector<Region> getAllRegions(SqliteHelper::unique_sqlite3& db)
{
    const char query[] = "SELECT name, abbreviation FROM regions";
    auto stmt = prepare_stmt(db, query);
    std::vector<Region> regions;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        Region region;
        region.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        region.abbreviation = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
        /* region.iconURL = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); */
        regions.push_back(region);
    }
    return regions;
}

std::vector<Rarity> getAllRarities(SqliteHelper::unique_sqlite3& db)
{
    const char query[] = "SELECT name FROM rarities";
    auto stmt = prepare_stmt(db, query);
    std::vector<Rarity> rarities;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        Rarity rarity;
        rarity.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        rarities.push_back(rarity);
    }
    return rarities;
}

std::vector<SpellSpeed> getAllSpellSpeeds(SqliteHelper::unique_sqlite3& db)
{
    const char query[] = "SELECT name FROM spellSpeeds";
    auto stmt = prepare_stmt(db, query);
    std::vector<SpellSpeed> spellSpeeds;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        SpellSpeed spellSpeed;
        spellSpeed.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        spellSpeeds.push_back(spellSpeed);
    }
    return spellSpeeds;
}


std::optional<Card> getCardById(SqliteHelper::unique_sqlite3& db, const std::string& cardCode)
{
    std::string query = GET_ALL_CARDS_QUERY + " WHERE cardCode = ?";
    auto stmt = prepare_stmt(db, query.c_str());
    sqlite3_bind_text(stmt.get(), 1, cardCode.c_str(), -1, NULL);
    auto cards = getCardsFromStatement(db, stmt);
    if(cards.size() == 1)
    {
        return cards[0];
    }
    if(cards.size() == 0) // No card found. OK
    {
        return {};
    }
    throw std::invalid_argument("Not unique card ids"); // That should never possibly happen. Maybe assert?
}
}
