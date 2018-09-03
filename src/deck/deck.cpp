#include "../card/card.hpp"
#include "deck.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <fstream>

void Deck::gatherCards() {
    cards = new std::vector<Card *>(52);
    std::vector<std::string> art(10);
    std::ifstream asciiArts("src/resources/ascii.txt");
    if (asciiArts.is_open()) {
        for (int i = 0; i < 52; i++) {
            for (int j = 0; j < 9; j++)  {
                std::getline(asciiArts, art[j]);
            }
            (*cards)[i] = new Card(art);
        }
    } else {
        std::cerr << "error: couldnt open ascii art" << std::endl;
        exit(1);
    }
};

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto randomNumberGenerator = std::default_random_engine(seed);
    std::shuffle(std::begin(*(cards)), std::end(*(cards)), randomNumberGenerator);
};

Card *Deck::drawCard() {
    Card *card = (*cards)[cards->size() - 1];
    cards->pop_back();
    return card;
};

void Deck::returnToDeck(std::vector<Card *> hand) {
    for (auto &i : hand) {
        cards->push_back(i);
    }
};







