#pragma once
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
    void addCard(Card &cardToAdd);
    void removeCard(Card &cardToRemove);
    int length();
    std::vector <Card> getCardsAsVector();
};