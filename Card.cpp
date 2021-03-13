#include "Card.hpp"
#include <string>

int Card::getCardCode()
{
    return this->cardCode;
}

std::string Card::getRegionRef()
{
    return this->regionRef;
}

int Card::getCost()
{
    return this->cost;
}

int Card::getHealth()
{
    return this->health;
}

int Card::getSpellSpeedRef()
{
    return this->spellSpeedRef;
}

int Card::getRarityRef()
{
    return this->rarityRef;
}

bool Card::isCollectible()
{
    return this->collectible;
}

std::string Card::getSet()
{
    return this->set;
}

std::string Card::getDescriptionRaw()
{
    return this->descriptionRaw;
}

std::string Card::getLevelupDescriptionRaw()
{
    return this->levelupDescriptionRaw;
}

std::string Card::getFlavorText()
{
    return this->flavorText;
}

std::string Card::getName()
{
    return this->name;
}

std::string Card::getSupertype()
{
    return this->supertype;
}

int Card::getType()
{
    return this->type;
}

std::vector<Card> Card::getAssociatedCards()
{
    return this->associatedCards;
}

std::vector<std::string> Card::getCardKeywords()
{
    return this->cardKeywords;
}

std::vector<std::string> Card::getCardSubtypes()
{
    return this->cardSubtypes;
}

std::map<std::string, std::string> Card::getCardAssets()
{
    return this->cardAssets;
}

void Card::setCardCode(int cardCode)
{
    this->cardCode = cardCode;
}

void Card::setRegionRef(std::string regionRef)
{
    this->regionRef = regionRef;
}

void Card::setAttack(int attack)
{
    this->attack = attack;
}

void Card::setCost(int cost)
{
    this->cost = cost;
}

void Card::setHealth(int health)
{
    this->health = health;
}

void Card::setSpellSpeedRef(int spellSpeedRef)
{
    this->spellSpeedRef = spellSpeedRef;
}

void Card::setRarityRef(int rarityRef)
{
    this->rarityRef = rarityRef;
}

void Card::setCollectible(bool collectible)
{
    this->collectible = collectible;
}

void Card::setSet(std::string set)
{
    this->set = set;
}

void Card::setDescriptionRaw(std::string descriptionRaw)
{
    this->descriptionRaw = descriptionRaw;
}

void Card::setLevelupDescriptionRaw(std::string levelupDescriptionRaw)
{
    this->levelupDescriptionRaw = levelupDescriptionRaw;
}

void Card::setFlavorText(std::string flavorText)
{
    this->flavorText = flavorText;
}

void Card::setName(std::string name)
{
    this->name = name;
}

void Card::setSupertype(std::string supertype)
{
    this->supertype = supertype;
}

void Card::setType(int type)
{
    this->type = type;
}

void Card::setAssociatedCards(std::vector<Card> associatedCards)
{
    this->associatedCards = associatedCards;
}

void Card::setCardKeywords(std::vector<std::string> cardKeywords)
{
    this->cardKeywords = cardKeywords;
}

void Card::setCardSubtypes(std::vector<std::string> cardSubtypes)
{
    this->cardSubtypes = cardSubtypes;
}

void Card::setCardAssets(std::map<std::string, std::string> cardAssets)
{
    this->cardAssets = cardAssets;
}