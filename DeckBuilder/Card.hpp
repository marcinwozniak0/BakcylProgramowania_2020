#include <vector>
#include <string>
#include <map>

class Card
{
private:
    std::string cardCode;
    std::string regionRef;
    int attack;
    int cost;
    int health;
    int spellSpeedRef;
    int rarityRef;
    bool collectible;
    std::string set;
    std::string descriptionRaw;
    std::string levelupDescriptionRaw;
    std::string flavorText;
    std::string name;
    std::string supertype;
    int type;
    std::vector<Card> associatedCards;
    std::vector<std::string> cardKeywords;
    std::vector<std::string> cardSubtypes;
    std::map<std::string, std::string> cardAssets;

public:
    std::string getCardCode();
    std::string getRegionRef();
    int getAttack();
    int getCost();
    int getHealth();
    int getSpellSpeedRef();
    int getRarityRef();
    bool isCollectible();
    std::string getSet();
    std::string getDescriptionRaw();
    std::string getLevelupDescriptionRaw();
    std::string getFlavorText();
    std::string getName();
    std::string getSupertype();
    int getType();
    std::vector<Card> getAssociatedCards();
    std::vector<std::string> getCardKeywords();
    std::vector<std::string> getCardSubtypes();
    std::map<std::string, std::string> getCardAssets();
    void setCardCode(std::string cardCode);
    void setRegionRef(std::string regionRef);
    void setAttack(int attack);
    void setCost(int cost);
    void setHealth(int health);
    void setSpellSpeedRef(int spellSpeedRef);
    void setRarityRef(int rarityRef);
    void setCollectible(bool collectible);
    void setSet(std::string set);
    void setDescriptionRaw(std::string descriptionRaw);
    void setLevelupDescriptionRaw(std::string levelupDescriptionRaw);
    void setFlavorText(std::string flavorText);
    void setName(std::string name);
    void setSupertype(std::string supertype);
    void setType(int type);
    void setAssociatedCards(std::vector<Card> associatedCards);
    void setCardKeywords(std::vector<std::string> cardKeywords);
    void setCardSubtypes(std::vector<std::string> cardSubtypes);
    void setCardAssets(std::map<std::string, std::string> cardAssets);
};
