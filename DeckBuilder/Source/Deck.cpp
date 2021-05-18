#include "Deck.hpp"

void Deck::addCard(CardApi::Card &cardToAdd) 
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

std::vector<CardApi::Card> Deck::getCardsAsVector() 
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
