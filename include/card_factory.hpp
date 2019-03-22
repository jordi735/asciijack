#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include <vector>
#include "card.hpp"

enum CardType {

    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES

};

enum CardValue {

    ACE,
    KING,
    QUEEN,
    JACK,
    TEN,
    NINE,
    EIGHT,
    SEVEN,
    SIX,
    FIVE,
    FOUR,
    THREE,
    TWO

};

class CardFactory {

    public:
        virtual Card *createCard(CardType, CardValue) = 0;

};

class SmallCardFactory : public CardFactory {

    public:
        Card *createCard(CardType, CardValue);

};

class NormalCardFactory : public CardFactory {

    public:
        Card *createCard(CardType, CardValue);

};

#endif
