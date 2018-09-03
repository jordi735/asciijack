#include "game/game.hpp"
#include <iostream>
int main() {

    system("clear");

    std::cout << (R"(                       .__.__     __               __      )") << std::endl;
    std::cout << (R"( _____    ______ _____ |__|__|   |__|____    ____ |  | __  )") << std::endl;
    std::cout << (R"( \__  \  /  ___// ____\|  |  |   |  \__  \ _/ ___\|  |/ /  )") << std::endl;
    std::cout << (R"(  / __ \_\___ \\  \____|  |  |   |  |/ __ \\  \___|    <   )") << std::endl;
    std::cout << (R"(  (____  /____  >\___  >__|__/\__|  (____  /\___  >__|_ \  )") << std::endl;
    std::cout << (R"(       \/     \/     \/      \______|    \/     \/     \/  )") << std::endl;
    std::cout << std::endl;

    Game blackjack;
    blackjack.setup();
    blackjack.play();
};
