#include "../Include/utilities.hpp"
#include <iostream>

std::vector<CardApi::Card> getCardsFromStatement(SqliteHelper::unique_sqlite3& db, SqliteHelper::unique_stmt& stmt)
{
    std::vector<CardApi::Card> cards;
    int rc;
    while ((rc = sqlite3_step(stmt.get())) == SQLITE_ROW)
    {
        CardApi::Card card;
        card.cardCode = SqliteHelper::getStringColumn(db, stmt, 0);
        card.name = SqliteHelper::getStringColumn(db, stmt, 1);
        card.attack = sqlite3_column_int(stmt.get(), 2);
        card.cost = sqlite3_column_int(stmt.get(), 3);
        card.health = sqlite3_column_int(stmt.get(), 4);
        card.artistName = SqliteHelper::getStringColumn(db, stmt, 5);
        card.isCollectible = sqlite3_column_int(stmt.get(), 6);
        card.description = SqliteHelper::getStringColumn(db, stmt, 7);
        card.levelupDescription = SqliteHelper::getStringColumn(db, stmt, 8);
        card.flavorText = SqliteHelper::getStringColumn(db, stmt, 9);
        card.supertype = SqliteHelper::getStringColumn(db, stmt, 10);
        card.type = SqliteHelper::getStringColumn(db, stmt, 11);
        card.set.name = SqliteHelper::getStringColumn(db, stmt, 12);
        card.set.abbreviation = SqliteHelper::getStringColumn(db, stmt, 13);
        card.region.name = SqliteHelper::getStringColumn(db, stmt, 14);
        card.region.abbreviation = SqliteHelper::getStringColumn(db, stmt, 15);
        card.rarity.name = SqliteHelper::getStringColumn(db, stmt, 16);
        card.spellSpeed.name = SqliteHelper::getStringColumn(db, stmt, 16);
        card.spellSpeed.name = SqliteHelper::getStringColumn(db, stmt, 17);
        cards.push_back(card);
    }
    return cards;
}
