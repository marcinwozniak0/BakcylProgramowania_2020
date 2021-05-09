#include "DeckBuilder.hpp"
#include "Deck.hpp"
#include "IllegalCardExceptions.hpp"

int DeckBuilder::checkNumberOfCard(CardApi::Card card) 

{
    int number = 0;
    for (auto c : deck.getCardsAsVector()) 
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
        else if (secondRegion == voidRegion)
        {
            secondRegion = cardToAdd.region;
        } 
        else if (!(firstRegion == cardToAdd.region || secondRegion == cardToAdd.region))
        {
            throw IllegalCardException("Invalid region");
            return;
        }

        if (cardToAdd.type == "hero" && deck.getNumberOfHeroes() < maxNumberOfHeroes) //TODO: correct type of hero, ask SQL(!)
        {       
            deck.increaseNumberOfHeroes();
            deck.addCard(cardToAdd);
        } 
        else if (cardToAdd.type == "hero" && deck.getNumberOfHeroes() >= maxNumberOfHeroes)
        {
            throw IllegalCardException("Too many heroes");
            return;
        }
        else 
        {
            deck.addCard(cardToAdd);
        }
    } 
    else if (deckLength >= maxNumberOfCards)
    {
        throw IllegalCardException("Too many cards");
        return;
    }
    else if (checkNumberOfCard(cardToAdd) >= maxNumberOfEachCard)
    {
        throw IllegalCardException("A card can't be added more than 3 times");
        return;
    }
    else if (deckLength < 0)
    {
        throw IllegalCardException("Too few cards");
        return;
    }
    else
    {
        throw IllegalCardException("Other exception");
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
                throw IllegalCardException("This card doesn't occur in this deck");
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
        throw IllegalCardException("There are no cards to remove");
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
        throw IllegalCardException("Invalid ID");
    }
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
        throw IllegalCardException("Invalid ID");
    }
}
