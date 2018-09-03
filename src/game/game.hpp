#ifndef GAME_HPP
#define GAME_HPP
#include "../deck/deck.hpp"
#include "../player/player.hpp"
#include <string>
class Game {
    private:
        Deck deck;
        Player *player;
        Player *computer;
        void gatherCards();
        void initialHandout();
        std::string *input;
        unsigned bet, jar;
        void printFunds();
        void getBet();
        bool confirmBet();
        std::string getUserTurn();
        void handleHit();
        void announceWinner(Player *);
        void activateSentientAI();
        void announceTie();
    public:
        void setup();
        void play();
};
#endif
