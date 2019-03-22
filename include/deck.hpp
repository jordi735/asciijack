#ifndef DECK_HPP
#define DECK_HPP

#include "card.hpp"
#include "card_factory.hpp"
#include <vector>

class Deck {
    private:
        CardFactory *factory;
        std::vector<Card *> *cards;

    public:
        Deck(CardFactory *);
        void create();
        void shuffle();
        void returnToDeck(std::vector<Card *>);
        Card *drawCard();
};

#endif
