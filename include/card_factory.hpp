#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include <vector>
#include "card.hpp"

enum CardEnum {

        ACE_CLUBS,
        ACE_DIAMONDS,
        ACE_HEARTS,
        ACE_SPADES,

        KING_CLUBS,
        KING_DIAMONDS,
        KING_HEARTS,
        KING_SPADES,

        QUEEN_CLUBS,
        QUEEN_DIAMONDS,
        QUEEN_HEARTS,
        QUEEN_SPADES,

        JACK_CLUBS,
        JACK_DIAMONDS,
        JACK_HEARTS,
        JACK_SPADES,

        TEN_CLUBS,
        TEN_DIAMONDS,
        TEN_HEARTS,
        TEN_SPADES,

        NINE_CLUBS,
        NINE_DIAMONDS,
        NINE_HEARTS,
        NINE_SPADES,

        EIGHT_CLUBS,
        EIGHT_DIAMONDS,
        EIGHT_HEARTS,
        EIGHT_SPADES,

        SEVEN_CLUBS,
        SEVEN_DIAMONDS,
        SEVEN_HEARTS,
        SEVEN_SPADES,

        SIX_CLUBS,
        SIX_DIAMONDS,
        SIX_HEARTS,
        SIX_SPADES,

        FIVE_CLUBS,
        FIVE_DIAMONDS,
        FIVE_HEARTS,
        FIVE_SPADES,

        FOUR_CLUBS,
        FOUR_DIAMONDS,
        FOUR_HEARTS,
        FOUR_SPADES,

        THREE_CLUBS,
        THREE_DIAMONDS,
        THREE_HEARTS,
        THREE_SPADES,

        TWO_CLUBS,
        TWO_DIAMONDS,
        TWO_HEARTS,
        TWO_SPADES

};

class CardFactory {

    public:
        std::vector<Card *> createSuit(CardEnum);
        Card *createCard(CardEnum);

};

#endif
