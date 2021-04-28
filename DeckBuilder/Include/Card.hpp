#pragma once
#ifndef CARD_HPP
#define CARD_HPP

#include <vector>
#include <string>
#include <map>

class Card
{
private:
    std::string cardCode;
    std::string region;
    int attack;
    int cost;
    int health;
    std::string spellSpeed;
    std::string rarity;
    bool collectible;
    std::string set;
    std::string descriptionRaw;
    std::string levelupDescriptionRaw;
    std::string flavorText;
    std::string name;
    std::string supertype;
    std::string type;
    std::vector<std::string> associatedCards;
    std::vector<std::string> cardKeywords;
    std::vector<std::string> cardSubtypes;
    std::map<std::string, std::string> cardAssets;

public:
    std::string getCardCode();
    std::string getRegion();
    int getAttack();
    int getCost();
    int getHealth();
    std::string getSpellSpeed();
    std::string getRarity();
    bool isCollectible();
    std::string getSet();
    std::string getDescriptionRaw();
    std::string getLevelupDescriptionRaw();
    std::string getFlavorText();
    std::string getName();
    std::string getSupertype();
    std::string getType();
    std::vector<std::string> getAssociatedCards();
    std::vector<std::string> getCardKeywords();
    std::vector<std::string> getCardSubtypes();
    std::map<std::string, std::string> getCardAssets();
    void setCardCode(std::string cardCode);
    void setRegion(std::string region);
    void setAttack(int attack);
    void setCost(int cost);
    void setHealth(int health);
    void setSpellSpeed(std::string spellSpeed);
    void setRarity(std::string rarity);
    void setCollectible(bool collectible);
    void setSet(std::string set);
    void setDescriptionRaw(std::string descriptionRaw);
    void setLevelupDescriptionRaw(std::string levelupDescriptionRaw);
    void setFlavorText(std::string flavorText);
    void setName(std::string name);
    void setSupertype(std::string supertype);
    void setType(std::string type);
    void setAssociatedCards(std::vector<std::string> associatedCards);
    void setCardKeywords(std::vector<std::string> cardKeywords);
    void setCardSubtypes(std::vector<std::string> cardSubtypes);
    void setCardAssets(std::map<std::string, std::string> cardAssets);
    bool operator==(const Card& other) const;
};

#endif