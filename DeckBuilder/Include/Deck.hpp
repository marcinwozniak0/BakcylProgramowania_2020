#pragma once
#include <string>
#include <vector>
#include "baseCardApi.hpp"

class Deck
{
    private:
    int numberOfHeroes;
    std::string firstRegion;
    std::string secondRegion;
    std::vector <CardApi::Card> deck;


    public:
    Deck();
    ~Deck();
    void addCard(CardApi::Card &cardToAdd);
    void removeCard(int i);
    int length();
    std::vector <CardApi::Card> getCardsAsVector();
    int getNumberOfHeroes();
    void increaseNumberOfHeroes();
    void decreaseNumberOfHeroes();
    void clearCards(){deck.clear();}
};
