#ifndef CARD_HPP
#define CARD_HPP

#include <vector>
#include <string>

class Card {

    public:
        virtual const unsigned short getWorth() = 0;
        virtual std::vector<std::string> getArt() = 0;

};

class NormalCard : public Card {
    private:
        std::vector<std::string> *ascii;

    public:
        NormalCard(std::vector<std::string>);
        const unsigned short getWorth();
        std::vector<std::string> getArt();
};

class SmallCard : public Card {
    private:
        std::vector<std::string> *ascii;

    public:
        SmallCard(std::vector<std::string>);
        const unsigned short getWorth();
        std::vector<std::string> getArt();
};

#endif
