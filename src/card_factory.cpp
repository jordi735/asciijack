#include "../include/card_factory.hpp"
#include <vector>
#include <iostream>
#include "../resources/ascii.hpp"

std::vector<Card *> CardFactory::createSuit(CardEnum type) {

    constexpr int suitSpace = 36;
    constexpr int cardWidth = 12;
    constexpr int cardHeight = 10;

    std::vector<Card *> cards(4);

    int currentChar, i = 0;
    while (type != static_cast<CardEnum>(i++));
    currentChar = ((i - 1) * suitSpace) * cardWidth;
    unsigned char *startAddress = (ascii_art + currentChar);

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
