#include "../deck/deck.hpp"
#include "game.hpp"
#include <iostream>

void Game::setup() {
    //std::cout << "enter player name > ";
    //std::string name;
    //std::cin >> name;
    std::cout << "setting up players..." << std::endl;
    system("sleep 1");
    player = new Player("player", 500);
    computer = new Player("dealer", 99999);
    std::cout << "building deck..." << std::endl;
    system("sleep 1");
    deck.create();
    std::cout << "shuffling deck..." << std::endl;
    system("sleep 1");
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
    std::cout << computer->getName() << " money: $" << computer->getMoney() << std::endl;
    std::cout << player->getName() << " money: $" << player->getMoney() << std::endl;
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

std::string Game::getUserTurn(bool doubleDown) {
    std::string choice;
    std::cout << "1) hit"  << std::endl;
    std::cout << "2) stay"  << std::endl;
    if (doubleDown && player->getMoney() >= bet) {
        std::cout << "3) double"  << std::endl;
    }
    std::cout << "enter number > ";
    std::cin >> choice;
    return choice;
};

void Game::announceWinner(Player *winner) {
    std::cout << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "the winner is: " << winner->getName() << std::endl;
};

void Game::handleHit() {
    player->addCard(deck.drawCard());
};

void Game::refreshScreen() {
    system("clear");
    computer->printHand();
    player->printHand();
};

void Game::refreshScreenHidden() {
    system("clear");
    computer->printHidden();
    player->printHand();
};

void Game::activateSentientAI() {
    refreshScreen();
    while (computer->getHandWorth() <= player->getHandWorth()) {
        system("sleep 1");
        refreshScreen();
        if (computer->getHandWorth() >= 17) {
            break;
        }
        computer->addCard(deck.drawCard());
        refreshScreen();
    }
};

void Game::announceTie() {
    std::cout << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << player->getName() << " and " << computer->getName() << " have tied!" << std::endl;
};

void Game::handleDouble() {
    handleHit();
    player->loseMoney(bet);
    computer->loseMoney(bet);
    jar *= 2;
    if (player->isBusted()) {
        return;
    }
    activateSentientAI();
};

void Game::errorMessage(std::string message) {
    std::cerr << message << std::endl;
    getchar();
    getchar();
};

bool Game::checkWinner() {

    refreshScreen();

    unsigned short computerHandWorth = computer->getHandWorth();
    unsigned short playerHandWorth = player->getHandWorth();

    if (player->isBusted()) {
        announceWinner(computer);
        computer->gainMoney(jar);
        return true;
    } else if (computer->isBusted()) {
        announceWinner(player);
        player->gainMoney(jar);
        return true;
    }

    if (computerHandWorth >= 17) {
        if (computerHandWorth == playerHandWorth) {
            announceTie();
            player->gainMoney(jar/2);
            computer->gainMoney(jar/2);
            return true;
        } else if (computerHandWorth > playerHandWorth) { // COMPUTER WINS
            announceWinner(computer);
            computer->gainMoney(jar);
            return true;
        } else if (computerHandWorth < playerHandWorth){
            announceWinner(player);
            player->gainMoney(jar);
            return true;
        }
    }

    return false;
};

bool Game::handleChoice(std::string choice, bool firstRound) {
    char sign = choice[0];
    if (sign == '1') {
        handleHit();
    } else if (sign == '2') {
        activateSentientAI();
    } else if (sign == '3') {
        if (!firstRound || player->getMoney() < bet) {
            errorMessage("error: cannot double");
            return false;
        } else {
            handleDouble();
        }
    } else {
        errorMessage("error: unknown option");
        return false;
    }

    return true;

};

void Game::play() {
    while (player->getMoney() > 0 && computer->getMoney() > 0) {
        // ONE BET ROUND
        bool firstRound = true;
        bet = jar = 0;
        gatherCards();
        initialHandout();
        printFunds();
        getBet();
        if (!confirmBet()) {
            errorMessage("error: not a valid bet");
            continue;
        }
        while (true) {
            refreshScreenHidden();
            std::string choice = getUserTurn((firstRound) ? true : false);

            if (handleChoice(choice, firstRound)) {
                firstRound = false;
            } else {
                continue;
            }

            if (checkWinner()) {
                break;
            }
        }
    }
};

