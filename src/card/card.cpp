#include "card.hpp"
#include <iostream>

Card::Card(std::vector<std::string> a) {
    ascii = new std::vector<std::string>(a);
};

const unsigned short Card::getWorth() {
    char sign = (*ascii)[1][1];
    if (isdigit(sign)) {
        if (sign == '1') {
            if ((*ascii)[1][2] == '0') {
                return 10;
            }
        } else {
            return static_cast<unsigned short>(sign - '0');
        }
    } else if (sign == 'A') {
        return 1;
    } else {
        return 10;
    }

    std::cerr << "error: empty card" << std::endl;
    return 0;
};

std::vector<std::string> Card::getArt() {
    return *ascii;
}
