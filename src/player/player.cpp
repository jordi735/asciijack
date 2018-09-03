#include "player.hpp"
#include "../card/card.hpp"
#include <vector>
#include <string>
#include <iostream>

Player::Player(std::string n, const unsigned m) {
    name = n;
    money = m;
};

const std::string Player::getName() {
    return name;
};

unsigned short Player::getHandWorth() {
    unsigned short total = 0;
    unsigned short amountAces = 0;

    for (auto &card : hand) {
        unsigned short worth = card->getWorth();
        if (worth == 1) {
            ++amountAces;
        } else {
            total += worth;
        }
    }

    while (amountAces--) {
        if (total + 11 + amountAces > 21) {
            total += 1;
        } else {
            total += 11;
        }
    }

    return total;
};

void Player::addCard(Card *card) {
    hand.push_back(card);
};

unsigned Player::getMoney() {
    return money;
};

void Player::loseMoney(unsigned m) {
    money -= m;
};

void Player::gainMoney(unsigned m) {
    money += m;
};

std::vector<Card *> Player::giveHand() {
    std::vector<Card *> handover(hand);
    hand.clear();
    return handover;
};

void Player::printHidden() {
    std::vector<std::string> backside;
    backside.push_back("  _________ ");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("|+++++++++|");
    backside.push_back("  ~~~~~~~~~ ");
    for (int i = 0; i < 9; i++) {
        std::cout << hand[0]->getArt()[i] << backside[i] << std::endl;
    }
};

bool Player::isBusted() {
    if (this->getHandWorth() > 21) {
        return true;
    }

    return false;
};

void Player::printHand() {
    for (int i = 0; i < 9; i++) {
        for (auto &s : hand) {
            std::cout << (s->getArt())[i];
            if (i == 0 || i == 8) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
};
