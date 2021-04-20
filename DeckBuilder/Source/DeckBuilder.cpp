#include "DeckBuilder.hpp"
#include "Deck.hpp"
#include "IllegalCardExceptions.hpp"

DeckBuilder::DeckBuilder()
{
    const int maxNumberOfCards = 40;
    const int maxNumberOfHeroes = 6;
    const int maxNumberOfEachCard = 3;
    std::string firstRegion = "";
    std::string secondRegion = "";
}

int DeckBuilder::checkNumberOfCard(Card card) 
{
    int number = 0;
    for (Card c : deck.getCardsAsVector()) 
    {
        if (c == card) 
        {
            number++;
        }
    }
    return number;
}

void DeckBuilder::addCard(Card &cardToAdd)
{
    int deckLength = deck.length();
    if (deckLength < maxNumberOfCards && deckLength >= 0 && checkNumberOfCard(cardToAdd) < maxNumberOfEachCard) 
    {
        if (firstRegion == "") 
        {
            firstRegion = cardToAdd.getRegion();
        } 
        else if (secondRegion == "") 
        {
            secondRegion = cardToAdd.getRegion();
        } 
        else if (!(firstRegion == cardToAdd.getRegion() || secondRegion == cardToAdd.getRegion())) 
        {
            throw IllegalCardException("Invalid region");
            return;
        }

        if (cardToAdd.getType() == "hero" && deck.getNumberOfHeroes() < maxNumberOfHeroes) //TODO: correct type of hero, ask SQL(!)
        {       
            deck.increaseNumberOfHeroes();
            deck.addCard(cardToAdd);
        } 
        else 
        {
            deck.addCard(cardToAdd);
        }
    } 
    else 
    {
        throw IllegalCardException("Too few or too many cards");
        return;
    }
}

void DeckBuilder::removeCard(Card &cardToRemove)
{
    int deckLength = deck.length();
    if (deckLength > 0)
    {
        for (int i = 0; i < deckLength; i++)
        {
            if (i == deckLength)
            {
                throw IllegalCardException("This card doesn't occur in this deck");
                return;
            }

            if (deck.getCardsAsVector().at(i) == cardToRemove)
            {
                std::string cardRegion = cardToRemove.getRegion();

                if (cardToRemove.getType() == "hero")
                {
                    deck.decreaseNumberOfHeroes();
                }

                deck.removeCard(i);
            
                int counter = 0;
                int deckLength = deck.length();
                for (int j = 0; j < deckLength; j++)
                {
                    if(deck.getCardsAsVector().at(j).getRegion() == cardRegion)
                    {
                        break;
                    } 
                    else 
                    {
                        counter++;
                    }
                }

                if (counter == deckLength)
                {
                    if (firstRegion == cardRegion)
                    {
                        firstRegion = "";
                        return;
                    } 
                    else if (secondRegion == cardRegion)
                    {
                        secondRegion = "";
                        return;
                    }
                }

                return;
            } 
        }
    }
    else
    {
        throw IllegalCardException("There is no cards to remove");
        return;
    }
}

DeckBuilder::~DeckBuilder() {}
