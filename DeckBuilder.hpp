#include <string>
#include <vector>

class DeckBuilder 
{
    void addCards(std::vector <std::string> cardsToAdd); //or <int> if we use ID
    void removeCards(std::vector <std::string> cardsToRemove); //or <int> if we use ID
    void deckValidator(std::vector <std::string> deck); //or <int> if we use ID
}; 