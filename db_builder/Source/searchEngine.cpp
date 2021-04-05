#include "searchEngine.hpp"
#include <optional>
#include <sqlite_helper.hpp>

struct DynamicQuery
{
    std::string queryText;
    std::vector<std::string> paramQueue;
    // Unfortunately we don't have nice heterogenous containers in cpp
    // so we resort to storing params in queue as strings.
    // If you want to queue integer you must convert it to string beforehand
    // This sucks, but drawbacks seem to be nonsignificant in our usecase
    void addFilters(const Filters& filters);
};

void DynamicQuery::addFilters(const Filters& filters)
{
    queryText += "WHERE 1=1";
    if (filters.cardName.size() > 0)
    {
        paramQueue.push_back(filters.cardName);
        queryText += " AND cards.name LIKE '%'|| ? ||'%'";
    }
    if (filters.regionNames.size() > 0)
    {
        paramQueue.insert(paramQueue.end(), filters.regionNames.begin(), filters.regionNames.end());
        queryText += " AND regions.name IN " + buildPlaceholdersList(filters.regionNames.size());
    }
    if (filters.minAttack.has_value())
    {
        paramQueue.push_back(std::to_string(*filters.minAttack));
        queryText += " AND attack >= ?";
    }
    if (filters.maxAttack.has_value())
    {
        paramQueue.push_back(std::to_string(*filters.maxAttack));
        queryText += " AND attack <= ?";
    }
}

void bindParamQueue(sqlite3_stmt* stmt, const std::vector<std::string>& paramQueue)
{
    for (size_t i = 0; i < paramQueue.size(); ++i)
    {
        const int paramIdx = i + 1; // sqlite3_bind() starts indexing from 1
        sqlite3_bind_text(stmt, paramIdx, paramQueue[i].c_str(), -1, NULL);
    }
}

std::vector<Card> searchCards(unique_sqlite3& db, const Filters& filters)
{
    DynamicQuery dynQuery;
    dynQuery.queryText = "SELECT cardCode, cards.name, attack, cost, health, artistName, "
                        "collectible, descriptionRaw, levelupDescriptionRaw, "
                        "flavorText, supertype, type FROM cards "
                        "LEFT JOIN regions ON cards.regionRef = regions.nameRef "
                        "LEFT JOIN sets ON cards.\"set\" = sets.nameRef "
                        "LEFT JOIN rarities ON cards.rarityRef = rarities.nameRef "
                        "LEFT JOIN spellSpeeds ON cards.spellSpeedRef = spellSpeeds.nameRef ";
    dynQuery.addFilters(filters);
    auto stmt = prepare_stmt(db, dynQuery.queryText.c_str());
    bindParamQueue(stmt, dynQuery.paramQueue);

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
