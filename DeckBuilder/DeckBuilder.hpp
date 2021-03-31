#include <string>
#include <vector>
#include "Card.hpp"
#include "Deck.hpp"

class DeckBuilder 
{
    private:
    int maxNumberOfCards;
    int maxNumberOfHeroes;
    int maxNumberOfEachCard;

    public:
    DeckBuilder();
    ~DeckBuilder();
    void addCard(Card &cardToAdd);
    void removeCard(Card &cardToRemove);
}; 