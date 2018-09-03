#ifndef CARD_HPP
#define CARD_HPP
#include <vector>
#include <string>
class Card {
    private:
        std::vector<std::string> *ascii;
    public:
        Card(std::vector<std::string>);
        const unsigned short getWorth();
        std::vector<std::string> getArt();
};
#endif
