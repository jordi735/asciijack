#include "player.hpp"
#include "../card/card.hpp"
#include <utility>
#include <vector>
#include <string>
#include <iostream>

Player::Player(std::string n, const unsigned m) {
    name = std::move(n);
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
    std::vector<std::string> handArt(9);
    for (int i = 0; i < 9; i++) {
        handArt[i] += " | ";
        handArt[i] += (hand[0]->getArt()[i]);
        if (i == 0) {
            handArt[i] += "  _________ ";
        } else if (i == 8) {
            handArt[i] += "  ~~~~~~~~~ ";
        } else {
            handArt[i] += "|+++++++++|";
        }
        handArt[i] += " | ";
    }
    for (auto &i : handArt) {
        std::cout << i << std::endl;
    }
};

bool Player::isBusted() {
    if (this->getHandWorth() > 21) {
        return true;
    }
    return false;
};

unsigned short Player::handSize() {
    return static_cast<unsigned short>(hand.size());
};

void Player::printHand() {
    std::vector<std::string> handArt(9);
    for (int i = 0; i < 9; i++) {
        handArt[i] += " | ";
        for (auto &s : hand) {
            handArt[i] += ((s->getArt())[i]);
            if (i == 0 || i == 8) {
                handArt[i] += " ";
            }
        }
        handArt[i] += " | ";
    }
    for (auto &i : handArt) {
        std::cout << i << std::endl;
    }
};
