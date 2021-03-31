#include <string>
#include <vector>
#include "Card.hpp"

class Deck
{
    private:
    int numberOfCards;
    int numberOfHeroes;
    std::string firstRegion;
    std::string secondRegion;
    std::vector <Card> deck;

    public:
    Deck();
    ~Deck();
    friend void addCard(Card &cardToAdd);
    friend void removeCard(Card &cardToRemove);
};