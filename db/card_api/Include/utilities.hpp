#pragma once
#include "../Include/baseCardApi.hpp"
#include "../../sqlite_helper/Include/sqlite_helper.hpp"
#include <string>

// Internal helper. This should be private header. TODO

// Query for getting all cards.
// You could use it as base for more advanced queries with filters
// Example:
// std::string filter = " WHERE cardCode = 2137";
// std::string filteredQuery = GET_ALL_CARDS_QUERY + filter;
const std::string GET_ALL_CARDS_QUERY = R"""(
    SELECT
     cardCode,
     cards.name,
     attack,
     cost,
     health,
     artistName,
     collectible,
     descriptionRaw,
     levelupDescriptionRaw,
     flavorText,
     supertype,
     'type',
     sets.name,
     sets.nameRef,
     regions.name,
     regions.abbreviation,
     rarities.name,
     spellSpeeds.name
    FROM cards
    LEFT JOIN regions
     ON cards.regionRef = regions.nameRef
    LEFT JOIN sets
     ON cards.'set' = sets.nameRef
    LEFT JOIN rarities
     ON cards.rarityRef = rarities.nameRef
    LEFT JOIN spellSpeeds
     ON cards.spellSpeedRef = spellSpeeds.nameRef
)""";

std::vector<CardApi::Card> getCardsFromStatement(SqliteHelper::unique_sqlite3& db, SqliteHelper::unique_stmt& stmt);
// Populates vector of cards with data returned by statement
// NOTE: Statement is assumed to be based on GET_ALL_CARDS_QUERY
// and must return same positioned columns
