#include "baseCardApi.hpp"
#include "searchEngine.hpp"
#include <iostream>

void searchExample(SqliteHelper::unique_sqlite3& db)
{
    CardApi::Pagination pagination;
    pagination.limit = 20;
    pagination.offset = 0;
    CardApi::Filters filters;
    /* filters.cardName = "niemoż"; */
    filters.regionNames = {"Ionia"};
    filters.setNames = {"Zew Góry"};
    filters.spellSpeedNames = {"Szybkie", "Błyskawiczne"};
    filters.minCost = 2;
    filters.maxCost = 4;
    filters.minHealth = 0;
    filters.maxHealth = 0;
    auto cards = CardApi::searchCards(db, filters, pagination);
    std::cout << cards.size() << "\n";
    for (auto& card : cards)
    {
        std::cout << card.name << " : " << card.cardCode << "\n";
    }
}

void getAllExample(SqliteHelper::unique_sqlite3& db)
{
    // This could be useful for dynamic population of buttons
    std::cout << "\nSety: \n";
    auto sets = CardApi::getAllSets(db);
    for (auto& set : sets)
    {
        std::cout << set.name << " : " << set.abbreviation << "\n";
    }

    std::cout << "\nRegiony: \n";
    auto regions = CardApi::getAllRegions(db);
    for (auto& region : regions)
    {
        std::cout << region.name << " : " << region.abbreviation << "\n";
    }

    std::cout << "\nRarities: \n";
    auto rarities = CardApi::getAllRarities(db);
    for (auto& rarity : rarities)
    {
        std::cout << rarity.name << "\n";
    }

    std::cout << "\nSpellSpeeds: \n";
    auto spellSpeeds = CardApi::getAllSpellSpeeds(db);
    for (auto& spellSpeed : spellSpeeds)
    {
        std::cout << spellSpeed.name << "\n";
    }
}

void searchFromUIExample(SqliteHelper::unique_sqlite3& db)
{
    // suggestion for using this api from UI
    // I used not-existing UI api to show how you could do it.
    // It is commented out due to usage of not-existing functions

    /* filters.regionNames = extractTickedCheckboxesToWhitelist(regionsCheckboxes); */
    /* if(minCostBox.isFilled()) */
    /* { */
    /*     filters.minCost = minCostBox.val; */
    /* } */
    /* if(maxCostBox.isFilled()) */
    /* { */
    /*     filters.minCost = maxCostBox.val; */
    /* } */
    /* //etc */
    /* filters.cardName = getTextBoxVal(cardNameBox); */
    /* pagination.limit = cardsPerPage; */
    /* pagination.offset = calcOffset(cardsPerPage, pageNumber) // could be just cardsPerPage * (pageNumber - 1). If you
     * want, we probably can keep that conversion at our place */

    // Fortunately, I'm not a front-end developer, but light layer just converting UI elems to STL containers feel more
    // reasonable for me than introducing another overcomplicated middleware object like `SearchRequest` proposed by UI
    // team
}

int main()
{
    auto db = SqliteHelper::open_db("database.sql");
    searchExample(db);
    getAllExample(db);
}
