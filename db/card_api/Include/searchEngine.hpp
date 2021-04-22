#pragma once
#include "baseCardApi.hpp"
#include "sqlite_helper.hpp"
#include <optional>
#include <string>
#include <vector>

struct Filters
{
    // empty filter means no filter
    std::string cardName; // currently matches "*name*". ASCII characters are case insensitive
    // regions, sets, rarities and spellspeeds are matched exact, you provide whitelist of names
    std::vector<std::string> regionNames;
    std::vector<std::string> setNames;
    std::vector<std::string> rarityNames;
    std::vector<std::string> spellSpeedNames;
    std::optional<int> minAttack;
    std::optional<int> maxAttack;
    std::optional<int> minCost;
    std::optional<int> maxCost;
    std::optional<int> minHealth;
    std::optional<int> maxHealth;
};

struct Pagination
{
    std::optional<int> limit;
    std::optional<int> offset;
    // offset is ignored if limit is empty
};

// TODO: Sorting

std::vector<Card> searchCards(unique_sqlite3& db, const Filters& filters, const Pagination& pagination);