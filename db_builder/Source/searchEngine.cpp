#include "searchEngine.hpp"
#include <optional>
#include <sqlite_helper.hpp>

std::pair<std::string, std::vector<std::string>> parseFilters(const Filters& filters)
{
    std::string queryFilterPart = "WHERE 1=1";
    std::vector<std::string> paramQueue;
    if (filters.cardName.size() > 0)
    {
        paramQueue.push_back(filters.cardName);
        queryFilterPart += " AND cards.name LIKE '%'|| ? ||'%'";
    }
    if (filters.regionNames.size() > 0)
    {
        queryFilterPart += " AND regions.name IN " + buildPlaceholdersList(filters.regionNames.size());
        paramQueue.insert(paramQueue.end(), filters.regionNames.begin(), filters.regionNames.end());
    }
    if(filters.minAttack.has_value())
    {
        paramQueue.push_back(std::to_string(*filters.minAttack)); // agh
        queryFilterPart += " AND attack >= ?";
    }
    if(filters.maxAttack.has_value())
    {
        paramQueue.push_back(std::to_string(*filters.maxAttack)); // agh
        queryFilterPart += " AND attack <= ?";
    }
    return {queryFilterPart, paramQueue};
}

void bindParamQueue(sqlite3_stmt* stmt, const std::vector<std::string>& paramQueue)
// This suck because and doesn't work for non-string params
{
    for (size_t i = 0; i < paramQueue.size(); ++i)
    {
        const int paramIdx = i + 1; // sqlite3_bind() starts indexing from 1
        sqlite3_bind_text(stmt, paramIdx, paramQueue[i].c_str(), -1, NULL);
    }
}

std::vector<Card> searchCards(unique_sqlite3& db, const Filters& filters)
{
    std::string query = "SELECT cardCode, cards.name, attack, cost, health, artistName, "
                        "collectible, descriptionRaw, levelupDescriptionRaw, "
                        "flavorText, supertype, type FROM cards "
                        "LEFT JOIN regions ON cards.regionRef = regions.nameRef "
                        "LEFT JOIN sets ON cards.\"set\" = sets.nameRef "
                        "LEFT JOIN rarities ON cards.rarityRef = rarities.nameRef "
                        "LEFT JOIN spellSpeeds ON cards.spellSpeedRef = spellSpeeds.nameRef ";

    auto [queryFilterPart, paramQueue] = parseFilters(filters);
    query += queryFilterPart;
    auto stmt = prepare_stmt(db, query.c_str());
    bindParamQueue(stmt, paramQueue);

    std::vector<Card> cards;
    int rc;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        Card card;
        card.cardCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        card.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        card.attack = sqlite3_column_int(stmt, 2);
        card.cost = sqlite3_column_int(stmt, 3);
        card.health = sqlite3_column_int(stmt, 4);
        card.artistName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
        card.isCollectible = sqlite3_column_int(stmt, 6);
        card.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7));
        card.levelupDescription = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
        card.flavorText = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 9));
        card.supertype = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        card.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 11));
        cards.push_back(card);
    }
    return cards;
}
