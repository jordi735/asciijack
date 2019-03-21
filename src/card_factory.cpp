#include "../include/card_factory.hpp"
#include <vector>
#include <iostream>
#include "../resources/ascii.hpp"

Card *CardFactory::createCard(CardEnum type) {

    constexpr int cardWidth = 12;
    constexpr int cardHeight = 9;

    Card *card;

    int startChar, i = 0;
    while (type != static_cast<CardEnum>(i++));
    startChar = (cardHeight * cardWidth) * (i - 1);
    unsigned char *startAddress = (ascii_art + startChar);

    std::vector<std::string> art;
    for (int j = 0; j < cardHeight; j++)  {
        std::string line;
        for (int k = 0; k < cardWidth - 1; k++) {
            line.push_back(*startAddress);
            ++startAddress;
        }
        ++startAddress;
        art.push_back(line);
    }

    return new Card(art);
}

std::vector<Card *> CardFactory::createSuit(CardEnum type) {

    constexpr int suitSpace = 36;
    constexpr int cardWidth = 12;
    constexpr int cardHeight = 10;

    std::vector<Card *> cards(4);

    int startChar, i = 0;
    while (type != static_cast<CardEnum>(i++));
    startChar = ((i - 1) * suitSpace) * cardWidth;
    unsigned char *startAddress = (ascii_art + startChar);

    for (int i = 0; i < 4; i++) {
        std::vector<std::string> art;
        for (int j = 0; j < cardHeight - 1; j++)  {
            std::string line;
            for (int k = 0; k < cardWidth - 1; k++) {
                line.push_back(*startAddress);
                ++startAddress;
            }
            ++startAddress;
            art.push_back(line);
        }

        cards[i] = new Card(art);
    }

    return cards;
}

