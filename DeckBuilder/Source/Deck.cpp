#include "Deck.hpp"

Deck::Deck()
{
    int numberOfHeroes = 0;
    std::string firstRegion = "";
    std::string secondRegion = "";
    std::vector <Card> deck;
}

void Deck::addCard(Card &cardToAdd) 
{
    deck.push_back(cardToAdd);
}

void Deck::removeCard(int i) 
{
    deck.erase(deck.begin() + i);
}

int Deck::length() 
{
    return deck.size();
}

std::vector <Card> Deck::getCardsAsVector() 
{
    return deck;
}

int Deck::getNumberOfHeroes()
{
    return numberOfHeroes;
}
void Deck::increaseNumberOfHeroes()
{
    numberOfHeroes++;
}

void Deck::decreaseNumberOfHeroes()
{
    numberOfHeroes--;
}

Deck::~Deck() {}