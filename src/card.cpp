#include "../include/card.hpp"
#include <iostream>
#include <utility>

SmallCard::SmallCard(std::vector<std::string> a) {
    ascii = new std::vector<std::string>(std::move(a));
}

NormalCard::NormalCard(std::vector<std::string> a) {
    ascii = new std::vector<std::string>(std::move(a));
}

const unsigned short NormalCard::getWorth() {
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
}

const unsigned short SmallCard::getWorth() {
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
}

std::vector<std::string> NormalCard::getArt() {
    return *ascii;
}

std::vector<std::string> SmallCard::getArt() {
    return *ascii;
}
