#include "../include/deck.hpp"
#include "../include/game.hpp"
#include "../include/card_factory.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void Game::milliSleep(unsigned n) {
    std::this_thread::sleep_for(std::chrono::milliseconds(n));
}

void Game::setup(CardFactory *factory) {
    this->deck = new Deck(factory);
    std::cout << "[+] setting up players..." << std::endl;
    milliSleep(500);
    player = new Player("player", 500);
    computer = new Player("dealer", 99999);
    std::cout << "[+] building deck..." << std::endl;
    milliSleep(500);
    deck->create();
    std::cout << "[+] shuffling deck..." << std::endl;
    milliSleep(500);
}

void Game::gatherCards() {
    deck->returnToDeck(player->giveHand());
    deck->returnToDeck(computer->giveHand());
    deck->shuffle();
}

void Game::initialHandout() {
    player->addCard(deck->drawCard());
    player->addCard(deck->drawCard());
    computer->addCard(deck->drawCard());
    computer->addCard(deck->drawCard());
}

void Game::printFunds() {
    std::cout << "[$] " << computer->getName() << " money: $" << computer->getMoney() << std::endl;
    std::cout << "[$] " << player->getName() << " money: $" << player->getMoney() << std::endl;
}

void Game::getBet() {
    std::cout << "[?] enter bet > $";
    input = new std::string();
    std::cin >> *input;
}

bool Game::confirmBet() {
    for (auto &i : *input) {
        if (!std::isdigit(i)) {
            return false;
        }
    }

    bet = static_cast<unsigned int>(std::stoi(*input));
    if (bet > player->getMoney() || bet > computer->getMoney()) {
        return false;
    }
    jar += bet * 2;
    computer->loseMoney(bet);
    player->loseMoney(bet);

    return true;
}

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
}

void Game::announceWinner(Player *winner) {
    std::cout << "[#] " << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << "[#] " << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "[!] the winner is: " << winner->getName() << std::endl;
}

void Game::handleHit() {
    player->addCard(deck->drawCard());
}

void Game::refreshScreen(bool hide) {
    system(CLEARCOMMAND);
    std::cout << "         +--------+" << std::endl;
    std::cout << "         | DEALER |" << std::endl;
    std::cout << "         +--------+" << std::endl;
    std::cout << " +-";
    for (int i = 0; i < computer->handSize(); i++) {
        std::cout << "-----------";
    }
    std::cout << "-+" << std::endl;
    (hide) ? computer->printHidden() : computer->printHand();
    std::cout << " +-";
    for (int i = 0; i < computer->handSize(); i++) {
        std::cout << "-----------";
    }
    std::cout << "-+" << std::endl;

    std::cout << "         +--------+" << std::endl;
    std::cout << "         | PLAYER |" << std::endl;
    std::cout << "         +--------+" << std::endl;
    std::cout << " +-";
    for (int i = 0; i < player->handSize(); i++) {
        std::cout << "-----------";
    }
    std::cout << "-+" << std::endl;
    player->printHand();
    std::cout << " +-";
    for (int i = 0; i < player->handSize(); i++) {
        std::cout << "-----------";
    }
    std::cout << "-+" << std::endl;
}

void Game::activateSentientAI() {
    refreshScreen(false);
    if (computer->getHandWorth() > player->getHandWorth()) {
        return;
    }
    while (computer->getHandWorth() <= player->getHandWorth()) {
        milliSleep(1000);
        refreshScreen(false);
        if (computer->getHandWorth() >= 17) {
            break;
        }
        computer->addCard(deck->drawCard());
        refreshScreen(false);
    }
}

void Game::announceTie() {
    std::cout << "[#] " << player->getName() << " hand: " << player->getHandWorth() << std::endl;
    std::cout << "[#] " << computer->getName() << " hand: " << computer->getHandWorth() << std::endl;
    std::cout << "[!] " << player->getName() << " and " << computer->getName() << " have tied!" << std::endl;
}

void Game::handleDouble() {
    handleHit();
    player->loseMoney(bet);
    computer->loseMoney(bet);
    jar *= 2;
    if (player->isBusted()) {
        return;
    }
    activateSentientAI();
}

void Game::errorMessage(std::string message) {
    std::cerr << message << std::endl;
    getchar();
    getchar();
}

bool Game::checkBusted() {
    refreshScreen(false);
    bool haveWinner = false;
    if (player->isBusted()) {
        announceWinner(computer);
        computer->gainMoney(jar);
        haveWinner = true;
    } else if (computer->isBusted()) {
        announceWinner(player);
        player->gainMoney(jar);
        haveWinner = true;
    }
    return haveWinner;
}

bool Game::checkComparison() {

    refreshScreen(false);
    bool haveWinner = false;

    unsigned short computerHandWorth = computer->getHandWorth();
    unsigned short playerHandWorth = player->getHandWorth();

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

    return haveWinner;
}

bool Game::handleChoice(std::string choice, bool *firstRound) {
    char sign = choice[0];
    bool winnerLoser = false;
    if (sign == '1') {
        handleHit();
        *firstRound = false;
        if (checkBusted()) {
            winnerLoser = true;
        }
    } else if (sign == '2') {
        activateSentientAI();
        if (checkBusted() || checkComparison()) {
            winnerLoser = true;
        }
    } else if (sign == '3') {
        handleDouble();
        *firstRound = false;
        if (checkBusted() || checkComparison()) {
            winnerLoser = true;
        }
    } else {
        errorMessage("[x] error: unknown option");
    }
    return winnerLoser;
}

void Game::play() {
    while (player->getMoney() > 0 && computer->getMoney() > 0) {
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
            refreshScreen(true);
            std::string choice = getUserTurn(firstRound);

            if (choice[0] == '3' && !firstRound) {
                continue;
            }

            if (handleChoice(choice, &firstRound)) {
                break;
            } 
        }
    }
}
