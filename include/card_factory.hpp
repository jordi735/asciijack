#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include <vector>
#include "card.hpp"

enum CardEnum {
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
        std::vector<Card *> createSuit(CardEnum);

};

#endif
