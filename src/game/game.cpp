#include "../deck/deck.hpp"
#include "game.hpp"
#include <iostream>

void Game::setup() {
    //std::cout << "enter player name > ";
    //std::string name;
    //std::cin >> name;
    player = new Player("player", 500);
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

void Game::printFunds() {
    std::cout << computer->getName() << " money: " << computer->getMoney() << std::endl;
    std::cout << player->getName() << " money: " << player->getMoney() << std::endl;
};

void Game::getBet() {
    std::cout << "enter bet > ";
    input = new std::string();
    std::cin >> *input;
};

bool Game::confirmBet() {
    for (auto &i : *input) {
        if (!std::isdigit(i)) {
            return false;
        }
    }

    bet = std::stoi(*input);
    if (bet > player->getMoney() || bet > computer->getMoney()) {
        return false;
    }
    jar += bet * 2;
    computer->loseMoney(bet);
    player->loseMoney(bet);

    return true;
};

std::string Game::getUserTurn() {
    std::string choice;
    std::cout << "1) hit"  << std::endl;
    std::cout << "2) stay"  << std::endl;
    std::cout << "enter number > ";
    std::cin >> choice;
    if (!choice.empty()) {
        return choice;
    } //TODO
};

void Game::announceWinner(Player *winner) {
    std::cout << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "the winner is: " << winner->getName() << std::endl;
};

void Game::handleHit() {
    player->addCard(deck.drawCard());
};

void Game::activateSentientAI() {
    computer->printHand();
    while (computer->getHandWorth() <= player->getHandWorth()) {
        system("sleep 1"); // TODO: MAKE POSIX
        if (computer->getHandWorth() >= 21) {
            computer->printHand();
            break;
        }
        computer->addCard(deck.drawCard());
        computer->printHand();
    }
};

void Game::announceTie() {
    std::cout << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << player->getName() << " and " << computer->getName() << " have tied!" << std::endl;
};

void Game::play() { // TODO: CLEAN THIS SHIT
    while (player->getMoney() > 0 && computer->getMoney() > 0) {
        // ONE BET ROUND
        bet = jar = 0;
        gatherCards();
        initialHandout();
        printFunds();
        getBet();
        if (!confirmBet()) {
            std::cout << "error: not a valid bet" << std::endl;
            continue;
        }
        computer->printHidden();
        while (true) {
            // HIT STAY 
            player->printHand();
            std::string choice = getUserTurn();

            if (choice[0] == '1') {
                // HIT
                handleHit();
                if (player->isBusted()) {
                    player->printHand();
                    announceWinner(computer);
                    computer->gainMoney(jar);
                    break;
                }
            } else if (choice[0] == '2') {
                // STAY
                activateSentientAI();
                if (computer->isBusted()) { // PLAYER WINS
                    player->gainMoney(jar);
                    announceWinner(player);
                    break;
                } else {
                    if (computer->getHandWorth() == player->getHandWorth()) { // TIE AT 21
                        announceTie();
                        std::cout << computer->getHandWorth() << std::endl;
                        player->gainMoney(jar/2);
                        computer->gainMoney(jar/2);
                    } else { // COMPUTER WINS
                        announceWinner(computer);
                        computer->gainMoney(jar);
                    }
                    break;
                }
            } else {
                std::cout << "error: unknown option" << std::endl;
            }
        }
    }
};

