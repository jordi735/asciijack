#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <string>
#include <vector>
#include "../card/card.hpp"
class Player {
    private:
        std::string name;
        std::vector<Card *> hand;
        unsigned money;
    public:
        Player(std::string, const unsigned);
        const std::string getName();
        void addCard(Card *);
        unsigned short getHandWorth();
        unsigned getMoney();
        void loseMoney(unsigned);
        std::vector<Card *> giveHand();
        void gainMoney(unsigned);
        void printHand();
        void printHidden();
        bool isBusted();
        unsigned short handSize();
};
#endif
