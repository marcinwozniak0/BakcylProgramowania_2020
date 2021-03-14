#include <string>
#include <vector>
#include "Card.hpp"

class DeckBuilder 
{
    private:
    int maxNumberOfCards;
    int maxNumberOfHeroes;
    int maxNumberOfEachCard;
    std::string firstRegion;
    std::string secondRegion;

    public:
    void addCards(std::vector <Card> &cardsToAdd); //or <int> if we use ID
    void removeCards(std::vector <Card> &cardsToRemove); //or <int> if we use ID
    void deckValidator(std::vector <Card> &deck); //or <int> if we use ID
}; 