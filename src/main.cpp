#include "game/game.hpp"
#include <iostream>
int main() {

    system("clear");
    std::vector<std::string> asciiBanner;
    asciiBanner.push_back(R"(                       .__.__     __               __      )");
    asciiBanner.push_back(R"( _____    ______ _____ |__|__|   |__|____    ____ |  | __  )");
    asciiBanner.push_back(R"( \__  \  /  ___// ____\|  |  |   |  \__  \ _/ ___\|  |/ /  )");
    asciiBanner.push_back(R"(  / __ \_\___ \\  \____|  |  |   |  |/ __ \\  \___|    <   )");
    asciiBanner.push_back(R"(  (____  /____  >\___  >__|__/\__|  (____  /\___  >__|_ \  )");
    asciiBanner.push_back(R"(       \/     \/     \/      \______|    \/     \/     \/  )");
    for (auto &i : asciiBanner) {
        std::cout << i << std::endl;
    }

    Game blackjack;
    blackjack.setup();
    blackjack.play();
};
