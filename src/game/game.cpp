#include "../deck/deck.hpp"
#include "game.hpp"
#include <iostream>

void Game::setup() {
    std::cout << "enter player name > ";
    std::string name;
    std::cin >> name;
    player = new Player(name, 500);
    computer = new Player("dealer", 500);
    deck.gatherCards();
    deck.shuffle();
};

void Game::gatherCards() {
    deck.returnToDeck(player->giveHand());
    deck.returnToDeck(computer->giveHand());
    deck.shuffle();
};

void Game::initialHandout() {
    player->addCard(deck.drawCard());
    player->addCard(deck.drawCard());
    computer->addCard(deck.drawCard());
    computer->addCard(deck.drawCard());
};

void Game::play() { // TODO: CLEAN THIS SHIT
    constexpr unsigned short max = 21;
    while (player->getMoney() > 0 && computer->getMoney() > 0) {
        gatherCards();
        initialHandout();
        computer->printHidden();
        unsigned bet, jar;
        bet = jar = 0;
        std::cout << computer->getName() << " money: " << computer->getMoney() << std::endl;
        std::cout << player->getName() << " money: " << player->getMoney() << std::endl;
        std::cout << "enter bet > ";
        std::cin >> bet;
        if (bet > player->getMoney() || bet > computer->getMoney()) {
            std::cout << "no money" << std::endl;
            continue;
        } else {
            jar += bet * 2;
            computer->loseMoney(bet);
            player->loseMoney(bet);
        }

        while (1) {
            player->printHand();
            std::string choice;
            std::cout << "hit or stay > ";
            std::cin >> choice;
            if (choice == "hit") {
                player->addCard(deck.drawCard());
                if (player->getHandWorth() > max) {
                    player->printHand();
                    std::cout << "you went over by: " << (player->getHandWorth() - max) << std::endl;
                    std::cout << computer->getName() << " won" << std::endl;
                    computer->gainMoney(jar);
                    break;
                }
            } else if (choice == "stay") {
                // DO COMPUTER STUFF
                while (computer->getHandWorth() < max && computer->getHandWorth() < player->getHandWorth()) {
                    computer->addCard(deck.drawCard());
                    computer->printHand();
                    system("sleep 1");
                    if (computer->getHandWorth() == player->getHandWorth() && computer->getHandWorth() >= 17) {
                        break;
                    }
                }
                if (computer->getHandWorth() > max ) {
                    // COMPUTER LOST
                    std::cout << computer->getName() << " lost!" << std::endl;
                    player->gainMoney(jar);
                } else if (computer->getHandWorth() == player->getHandWorth()) {
                    // TIE
                    std::cout << "its a tie!" << std::endl;
                    player->gainMoney(jar/2);
                    computer->gainMoney(jar/2);
                } else {
                    // PLAYER LOST
                    computer->gainMoney(jar);
                    std::cout << player->getName() << " lost!" << std::endl;
                }
                std::cout << player->getName() << " handworth: " << player->getHandWorth() << std::endl;
                std::cout << computer->getName() << " handworth: " << computer->getHandWorth() << std::endl;
                bet = jar = 0;
                break;
            }

        }
    }
};

