#include "DeckBuilder.hpp"
#include "Deck.hpp"
#include "IllegalCardExceptions.hpp"
#include "../../ErrorWindow.h"

#include <iostream>
int DeckBuilder::checkNumberOfCard(CardApi::Card card) 

{
    int number = 0;
    for (const auto& c : deck.getCardsAsVector())
    {
        if (c == card) 
        {
            number++;
        }
    }
    return number;
}

void DeckBuilder::addCard(CardApi::Card &cardToAdd)
{
    CardApi::Region voidRegion;

    int deckLength = deck.length();
    if (deckLength < maxNumberOfCards && deckLength >= 0 && checkNumberOfCard(cardToAdd) < maxNumberOfEachCard)
    {
        if (firstRegion == voidRegion)
        {
            firstRegion = cardToAdd.region;
        } 
        else if (secondRegion == voidRegion && !(cardToAdd.region == firstRegion))
        {
            secondRegion = cardToAdd.region;
        } 
        else if (!(firstRegion == cardToAdd.region || secondRegion == cardToAdd.region))
        {
            ErrorWindow("Invalid region");
            return;
        }

        if (cardToAdd.type == "hero" && deck.getNumberOfHeroes() < maxNumberOfHeroes) //TODO: correct type of hero, ask SQL(!)
        {       
            deck.increaseNumberOfHeroes();
            deck.addCard(cardToAdd);          
        } 
        else if (cardToAdd.type == "hero" && deck.getNumberOfHeroes() >= maxNumberOfHeroes)
        {
            ErrorWindow("Too many heroes");
            return;
        }
        else 
        {
            deck.addCard(cardToAdd);
        }

        if(cardCount[cardToAdd] >= 1)
        {
            cardCount[cardToAdd]++;
        }
        else
        {
            cardCount[cardToAdd] = 1;
        }
    } 
    else if (deckLength >= maxNumberOfCards)
    {
        ErrorWindow("Too many cards");
        return;
    }
    else if (checkNumberOfCard(cardToAdd) >= maxNumberOfEachCard)
    {
        ErrorWindow("A card can't be added more than 3 times");
        return;
    }
    else if (deckLength < 0)
    {
        ErrorWindow("Too few cards");
        return;
    }
    else
    {
        ErrorWindow("Other exception");
        return;
    }
    
}

void DeckBuilder::removeCard(CardApi::Card &cardToRemove)
{
    CardApi::Region voidRegion;
    int deckLength = deck.length();
    if (deckLength > 0)
    {
        for (int i = 0; i < deckLength; i++)
        {
            if (i == deckLength)
            {
                ErrorWindow("This card doesn't occur in this deck");
                return;
            }

            if (deck.getCardsAsVector().at(i) == cardToRemove)
            {
                CardApi::Region cardRegion = cardToRemove.region;

                if (cardToRemove.type == "hero")
                {
                    deck.decreaseNumberOfHeroes();
                }

                deck.removeCard(i);
                cardCount[cardToRemove]--;
                if (cardCount[cardToRemove] <= 0 )
                {
                    cardCount.erase(cardToRemove);
                }
                int counter = 0;
                int deckLength = deck.length();
                for (int j = 0; j < deckLength; j++)
                {
                    if(deck.getCardsAsVector().at(j).region == cardRegion)
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
                        firstRegion = voidRegion;
                        return;
                    } 
                    else if (secondRegion == cardRegion)
                    {
                        secondRegion = voidRegion;
                        return;
                    }
                }

                return;
            } 
        }
    }
    else
    {
        ErrorWindow("There are no cards to remove");
        return;
    }
}

void DeckBuilder::addCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode)
{
    std::optional<CardApi::Card> card = CardApi::getCardById(db, cardCode);

    if (card.has_value())
    {
        addCard(card.value());
    }
    else
    {
        ErrorWindow("Invalid ID");
    }
}

void DeckBuilder::removeCardStack(CardApi::Card &cardToRemove)
{
   while(cardCount[cardToRemove] > 0)
   {
    removeCard(cardToRemove);
   }
   cardCount.erase(cardToRemove);
}

void DeckBuilder::removeCardByID (SqliteHelper::unique_sqlite3& db, const std::string& cardCode)
{
    std::optional<CardApi::Card> card = CardApi::getCardById(db, cardCode);

    if (card.has_value())
    {
        removeCard(card.value());
    }
    else
    {
        ErrorWindow("Invalid ID");
    }
}

std::map<CardApi::Card,int> DeckBuilder::getCardCountMap()
{
  return cardCount;
}
void DeckBuilder::resetDeck()
{
    cardCount.clear();
    deck.clearCards();
    firstRegion.name = "";
    secondRegion.name = "";
}
