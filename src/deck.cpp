#include "../include/card.hpp"
#include "../include/deck.hpp"
#include "../resources/ascii.hpp"
#include "../include/card_factory.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <fstream>

void Deck::create() {
    CardFactory factory;
    cards = new std::vector<Card *>;
    for (int i = ACE_CLUBS; i != TWO_SPADES+1; i++) {
        cards->push_back(factory.createCard(static_cast<CardEnum>(i)));
    }
    /*
    factory.createCard(static_cast<CardEnum>(0));
    factory.createCard(static_cast<CardEnum>(1));
    factory.createCard(static_cast<CardEnum>(2));
    factory.createCard(static_cast<CardEnum>(3));
    factory.createCard(static_cast<CardEnum>(1));
    */
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
