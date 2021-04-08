#include "Card.hpp"

std::string Card::getCardCode()
{
    return cardCode;
}

std::string Card::getRegionRef()
{
    return regionRef;
}

int Card::getCost()
{
    return cost;
}

int Card::getHealth()
{
    return health;
}

int Card::getSpellSpeedRef()
{
    return spellSpeedRef;
}

int Card::getRarityRef()
{
    return rarityRef;
}

bool Card::isCollectible()
{
    return collectible;
}

std::string Card::getSet()
{
    return set;
}

std::string Card::getDescriptionRaw()
{
    return descriptionRaw;
}

std::string Card::getLevelupDescriptionRaw()
{
    return levelupDescriptionRaw;
}

std::string Card::getFlavorText()
{
    return flavorText;
}

std::string Card::getName()
{
    return name;
}

std::string Card::getSupertype()
{
    return supertype;
}

int Card::getType()
{
    return type;
}

std::vector<Card> Card::getAssociatedCards()
{
    return associatedCards;
}

std::vector<std::string> Card::getCardKeywords()
{
    return cardKeywords;
}

std::vector<std::string> Card::getCardSubtypes()
{
    return cardSubtypes;
}

std::map<std::string, std::string> Card::getCardAssets()
{
    return cardAssets;
}

void Card::setCardCode(std::string cardCode1)
{
    cardCode = cardCode1;
}

void Card::setRegionRef(std::string regionRef1)
{
    regionRef = regionRef1;
}

void Card::setAttack(int attack1)
{
    attack = attack1;
}

void Card::setCost(int cost1)
{
    cost = cost1;
}

void Card::setHealth(int health1)
{
    health = health1;
}

void Card::setSpellSpeedRef(int spellSpeedRef1)
{
    spellSpeedRef = spellSpeedRef1;
}

void Card::setRarityRef(int rarityRef1)
{
    rarityRef = rarityRef1;
}

void Card::setCollectible(bool collectible1)
{
    collectible = collectible1;
}

void Card::setSet(std::string set1)
{
    set = set1;
}

void Card::setDescriptionRaw(std::string descriptionRaw1)
{
    descriptionRaw = descriptionRaw1;
}

void Card::setLevelupDescriptionRaw(std::string levelupDescriptionRaw1)
{
    levelupDescriptionRaw = levelupDescriptionRaw1;
}

void Card::setFlavorText(std::string flavorText1)
{
    flavorText = flavorText1;
}

void Card::setName(std::string name1)
{
    name = name1;
}

void Card::setSupertype(std::string supertype1)
{
    supertype = supertype1;
}

void Card::setType(int type1)
{
    type = type1;
}

void Card::setAssociatedCards(std::vector<Card> associatedCards1)
{
    associatedCards = associatedCards1;
}

void Card::setCardKeywords(std::vector<std::string> cardKeywords1)
{
    cardKeywords = cardKeywords1;
}

void Card::setCardSubtypes(std::vector<std::string> cardSubtypes1)
{
    cardSubtypes = cardSubtypes1;
}

void Card::setCardAssets(std::map<std::string, std::string> cardAssets1)
{
    cardAssets = cardAssets1;
}
