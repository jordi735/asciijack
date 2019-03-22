#ifndef GAME_HPP
#define GAME_HPP

#include "deck.hpp"
#include "player.hpp"
#include "card_factory.hpp"
#include <string>

#ifdef _WIN32
#define CLEARCOMMAND "CLS"
#endif

#ifdef unix
#define CLEARCOMMAND "clear"
#endif

class Game {
    private:
        Deck *deck;
        Player *player;
        Player *computer;
        void gatherCards();
        void initialHandout();
        std::string *input;
        unsigned bet, jar;
        void printFunds();
        void getBet();
        bool confirmBet();
        std::string getUserTurn(bool);
        void handleHit();
        void announceWinner(Player *);
        void activateSentientAI();
        void announceTie();
        bool checkBusted();
        bool checkComparison();
        void refreshScreen(bool);
        bool handleChoice(std::string, bool *);
        void handleDouble();
        void errorMessage(std::string);
        void milliSleep(unsigned);

    public:
        void setup(CardFactory *);
        void play();
};

#endif
