#ifndef GAME_HPP
#define GAME_HPP
#include "../deck/deck.hpp"
#include "../player/player.hpp"
class Game {
    private:
        Deck deck;
        Player *player;
        Player *computer;
        void gatherCards();
        void initialHandout();
    public:
        void setup();
        void play();
};
#endif
