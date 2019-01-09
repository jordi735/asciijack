#include "../include/card.hpp"
#include "../include/deck.hpp"
#include "../resources/ascii.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <fstream>

void Deck::create() {
    cards = new std::vector<Card *>(52);
    unsigned char *ascii_p = ascii_art;
    for (int i = 0; i < 52; i++) {
        std::vector<std::string> art;
        for (int j = 0; j < 9; j++)  {
            std::string line;
            for (int k = 0; k < 11; k++) {
                line.push_back(*ascii_p);
                ++ascii_p;
            }
            ++ascii_p;
            art.push_back(line);
        }
        (*cards)[i] = new Card(art);
    }
}

void Deck::shuffle() {
    long seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto randomNumberGenerator = std::default_random_engine(seed);
    std::shuffle(std::begin(*(cards)), std::end(*(cards)), randomNumberGenerator);
}

Card *Deck::drawCard() {
    Card *card = (*cards)[cards->size() - 1];
    cards->pop_back();
    return card;
}

void Deck::returnToDeck(std::vector<Card *> hand) {
    for (auto &i : hand) {
        cards->push_back(i);
    }
}
