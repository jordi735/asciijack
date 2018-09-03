#include "../deck/deck.hpp"
#include "game.hpp"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32
#define CLEARCOMMAND "CLS"
#endif

#ifdef linux
#define CLEARCOMMAND "clear"
#endif

void Game::milliSleep(unsigned n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
};

void Game::setup() {
    std::cout << "[+] setting up players..." << std::endl;
    milliSleep(500);
    player = new Player("player", 500);
    computer = new Player("dealer", 99999);
    std::cout << "[+] building deck..." << std::endl;
    milliSleep(500);
    deck.create();
    std::cout << "[+] shuffling deck..." << std::endl;
    milliSleep(500);
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
    std::cout << "[$] " << computer->getName() << " money: $" << computer->getMoney() << std::endl;
    std::cout << "[$] " << player->getName() << " money: $" << player->getMoney() << std::endl;
};

void Game::getBet() {
    std::cout << "[?] enter bet > ";
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
    std::cout << " 1) hit"  << std::endl;
    std::cout << " 2) stay"  << std::endl;
    if (doubleDown && player->getMoney() >= bet) {
        std::cout << " 3) double"  << std::endl;
    }
    std::cout << "[?] enter number > ";
    std::cin >> choice;
    return choice;
};

void Game::announceWinner(Player *winner) {
    std::cout << "[#] " << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << "[#] " << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "[!] the winner is: " << winner->getName() << std::endl;
};

void Game::handleHit() {
    player->addCard(deck.drawCard());
};

void Game::refreshScreen() {
    system(CLEARCOMMAND);
    computer->printHand();
    player->printHand();
};

void Game::refreshScreenHidden() {
    system(CLEARCOMMAND);
    computer->printHidden();
    player->printHand();
};

void Game::activateSentientAI() {
    refreshScreen();
    if (computer->getHandWorth() > player->getHandWorth()) {
        return;
    }
    while (computer->getHandWorth() <= player->getHandWorth()) {
        milliSleep(1000);
        refreshScreen();
        if (computer->getHandWorth() >= 17) {
            break;
        }
        computer->addCard(deck.drawCard());
        refreshScreen();
    }
};

void Game::announceTie() {
    std::cout << "[#] " << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << "[#] " << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "[!] " << player->getName() << " and " << computer->getName() << " have tied!" << std::endl;
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
    bool haveWinner = false;

    unsigned short computerHandWorth = computer->getHandWorth();
    unsigned short playerHandWorth = player->getHandWorth();

    if (player->isBusted()) {
        announceWinner(computer);
        computer->gainMoney(jar);
        haveWinner = true;
    } else if (computer->isBusted()) {
        announceWinner(player);
        player->gainMoney(jar);
        haveWinner = true;
    } else {
        if (computerHandWorth >= 17) {
            if (computerHandWorth == playerHandWorth) {
                announceTie();
                player->gainMoney(jar/2);
                computer->gainMoney(jar/2);
                haveWinner = true;
            } else if (computerHandWorth > playerHandWorth) {
                announceWinner(computer);
                computer->gainMoney(jar);
                haveWinner = true;
            } else if (computerHandWorth < playerHandWorth){
                announceWinner(player);
                player->gainMoney(jar);
                haveWinner = true;
            }
        } else {
            if (computerHandWorth > playerHandWorth) {
                announceWinner(computer);
                computer->gainMoney(jar);
                haveWinner = true;
            }
        }
    }

    return haveWinner;
};

bool Game::handleChoice(std::string choice, bool firstRound) {
    char sign = choice[0];
    if (sign == '1') {
        handleHit();
    } else if (sign == '2') {
        activateSentientAI();
    } else if (sign == '3') {
        if (!firstRound || player->getMoney() < bet) {
            errorMessage("[x] error: cannot double");
            return false;
        } else {
            handleDouble();
        }
    } else {
        errorMessage("[x] error: unknown option");
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
            errorMessage("[x] error: not a valid bet");
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
    if (!player->getMoney()) {

        std::cout << R"(    _________    _____   ____     _______  __ ___________  )" << std::endl;
        std::cout << R"(   / ___\__  \  /     \_/ __ \   /  _ \  \/ // __ \_  __ \ )" << std::endl;
        std::cout << R"(  / /_/  > __ \|  Y Y  \  ___/  (  <_> )   /\  ___/|  | \/ )" << std::endl;
        std::cout << R"(  \___  (____  /__|_|  /\___  >  \____/ \_/  \___  >__|    )" << std::endl;
        std::cout << R"( /_____/     \/      \/     \/                   \/        )" << std::endl;
        std::cout << std::endl;

    }
};

