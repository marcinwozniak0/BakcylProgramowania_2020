#include "utilities.hpp"
#include <iostream>

std::vector<CardApi::Card> getCardsFromStatement(SqliteHelper::unique_sqlite3& db, SqliteHelper::unique_stmt& stmt)
// Populates vector of cards with data returned by statement
// NOTE: Statement is assumed to be based on GET_ALL_CARDS_QUERY
// and must return same positioned columns
{
    std::vector<CardApi::Card> cards;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        CardApi::Card card;
        card.cardCode = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 0));
        card.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 1));
        card.attack = sqlite3_column_int(stmt.get(), 2);
        card.cost = sqlite3_column_int(stmt.get(), 3);
        card.health = sqlite3_column_int(stmt.get(), 4);
        card.artistName = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 5));
        card.isCollectible = sqlite3_column_int(stmt.get(), 6);
        card.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 7));
        card.levelupDescription = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 8));
        card.flavorText = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 9));
        card.supertype = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 10));
        card.type = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 11));
        card.set.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 12));
        card.set.abbreviation = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 13));
        card.region.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 14));
        card.region.abbreviation = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 15));
        card.rarity.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 16));
        card.spellSpeed.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt.get(), 17));
        cards.push_back(card);
    }
    return cards;
}
