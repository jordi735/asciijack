#ifndef DECK_HPP
#define DECK_HPP
#include "../card/card.hpp"
#include <vector>
class Deck {
    private:
        std::vector<Card *> *cards;
    public:
        void gatherCards();
        void shuffle();
        Card *drawCard();
};
#endif
