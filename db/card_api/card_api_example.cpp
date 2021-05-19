#include "baseCardApi.hpp"
#include "searchEngine.hpp"
#include <iostream>

void printCard(CardApi::Card card)
{
    std::cout << "Name: " << card.name << "\n"
              << "Id: " << card.cardCode << "\n"
              << "Attack: " << card.attack << "\n"
              << "Cost: " << card.cost << "\n"
              << "Health: " << card.health << "\n"
              << "Artist name: " << card.artistName << "\n"
              << "Is collectible: " << card.isCollectible << "\n"
              << "Description: " << card.description << "\n"
              << "Levelup description: " << card.levelupDescription << "\n"
              << "Flavor text: " << card.flavorText << "\n"
              << "Supertype: " << card.supertype << "\n"
              << "Type: " << card.type << "\n"
              << "Set name: " << card.set.name << "\n"
              << "Set abbreviation: " << card.set.abbreviation << "\n"
              << "Region name: " << card.region.name << "\n"
              << "Region abbreviation: " << card.region.abbreviation << "\n"
              << "Rarity name: " << card.rarity.name << "\n"
              << "SpellSpeed name: " << card.spellSpeed.name << "\n";
}

void searchExample(SqliteHelper::unique_sqlite3& db)
{
    std::cout<<"\n---------------------\n";
    std::cout<<"Search example\n";
    std::cout<<"---------------------\n";

    CardApi::Pagination pagination;
    pagination.limit = 20;
    pagination.offset = 0;
    CardApi::Filters filters;
    /* filters.cardName = "niemoż"; */
    filters.regionNames = {"Ionia"};
    /* filters.setNames = {"Zew Góry"}; */
    /* filters.spellSpeedNames = {"Szybkie", "Błyskawiczne"}; */
    filters.minCost = 2;
    filters.maxCost = 4;
    filters.minHealth = 0;
    filters.maxHealth = 0;
    auto cardsCodes = CardApi::searchCards(db, filters);
    std::cout << "Liczba znalezionych kart: " << cardsCodes.size() << "\n";
    for (auto& cardCode : cardsCodes)
    {
        std::cout<<"\n--\n";
        std::cout << cardCode << "\n";
        std::cout << "Icon path: " << CardApi::getBasicCardIconPath("en_us", cardCode) << "\n";
    }
}

void getAllExample(SqliteHelper::unique_sqlite3& db)
{
    // This could be useful for dynamic population of buttons
    std::cout<<"\n---------------------\n";
    std::cout<<"getAll example\n";
    std::cout<<"---------------------\n";
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

void getCardByIdExample(SqliteHelper::unique_sqlite3& db)
{
    std::cout<<"\n---------------------\n";
    std::cout<<"getCardById example\n";
    std::cout<<"---------------------\n";

    std::optional<CardApi::Card> card = CardApi::getCardById(db, "2137JP2DGMD"); // obviously invalid id
    if (card.has_value())
    {
        printCard(*card);
        std::cout << "\n";
    }
    card = CardApi::getCardById(db, "01NX014"); // valid id
    if (card.has_value())
    {
        printCard(*card);
        std::cout << "\n";
    }
}

int main()
{
    auto db = SqliteHelper::open_db("database.sql");
    searchExample(db);
    getAllExample(db);
    getCardByIdExample(db);
}
