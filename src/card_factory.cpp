#include "../include/card_factory.hpp"
#include <vector>
#include <iostream>
#include "../resources/ascii.hpp"

Card *CardFactory::createCard(CardType type, CardValue value) {

    constexpr int cardWidth = 12;
    constexpr int cardHeight = 9;

    int startChar = ((cardHeight * cardWidth) * 4) * static_cast<int>(value);
    startChar += (type * (cardHeight * cardWidth));
    const unsigned char *startAddress = (ascii_art + startChar);

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

