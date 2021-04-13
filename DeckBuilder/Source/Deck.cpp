#include "Deck.hpp"

Deck::Deck()
{
    int numberOfCards = 0;
    int numberOfHeroes = 0;
    std::string firstRegion = "";
    std::string secondRegion = "";
    std::vector <Card> deck;
}

void Deck::addCard(Card &cardToAdd) 
{
    deck.push_back(cardToAdd);
}

void Deck::removeCard(Card &cardToremove) 
{
    
}

int Deck::length() 
{
    return deck.size();
}

std::vector <Card> Deck::getCardsAsVector() 
{
    return deck;
}

Deck::~Deck() {}