#include "sqlite_helper.hpp"
#include <string>
#include <vector>
#include <optional>

/* struct Set */
/* { */
/*     std::string name; */
/*     std::string iconURL; */
/* }; */

/* struct Region */
/* { */
/*     std::string name; */
/*     std::string abbreviation; */
/*     std::string iconURL: */
/* }; */

/* struct Rarity */
/* { */
/*     std::string name; */
/* }; */

/* struct SpellSpeed */
/* { */
/*     std::string name; */
/* }; */

struct Card
{
    std::string cardCode;
    std::string name;
    int attack;
    int cost;
    int health;
    std::string artistName;
    bool isCollectible;
    std::string description;
    std::string levelupDescription;
    std::string flavorText;
    std::string supertype;
    std::string type;
    // It might be good idea to prefetch sets, regions, rarities and spellSpeeds
    // and store just references here. They are repeating a lot across cards
    /* Set set; */
    /* Region region; */
    /* Rarity rarity; */
    /* SpellSpeed spellSpeed; */
};

struct Filters
{
    // empty filter means no filter
    std::string cardName; // currently matches "*name*". ASCII characters are case insensitive
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

std::vector<Card> searchCards(unique_sqlite3& db, const Filters& filters);
