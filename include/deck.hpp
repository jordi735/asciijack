#ifndef DECK_HPP
#define DECK_HPP

#include "card.hpp"
#include <vector>

class Deck {
    private:
        std::vector<Card *> *cards;

    public:
        void create();
        void shuffle();
        void returnToDeck(std::vector<Card *>);
        Card *drawCard();
};

#endif
