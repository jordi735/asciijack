#include "../include/game.hpp"
#include <iostream>
int main() {

    system(CLEARCOMMAND);

    std::cout << (R"(                       .__.__     __               __      )") << std::endl;
    std::cout << (R"( _____    ______ _____ |__|__|   |__|____    ____ |  | __  )") << std::endl;
    std::cout << (R"( \__  \  /  ___// ____\|  |  |   |  \__  \ _/ ___\|  |/ /  )") << std::endl;
    std::cout << (R"(  / __ \_\___ \\  \____|  |  |   |  |/ __ \\  \___|    <   )") << std::endl;
    std::cout << (R"(  (____  /____  >\___  >__|__/\__|  (____  /\___  >__|_ \  )") << std::endl;
    std::cout << (R"(       \/     \/     \/      \______|    \/     \/     \/  )") << std::endl;
    std::cout << std::endl;

    Game blackjack{};
    blackjack.setup();
    blackjack.play();

    std::cout << R"(    _________    _____   ____     _______  __ ___________  )" << std::endl;
    std::cout << R"(   / ___\__  \  /     \_/ __ \   /  _ \  \/ // __ \_  __ \ )" << std::endl;
    std::cout << R"(  / /_/  > __ \|  Y Y  \  ___/  (  <_> )   /\  ___/|  | \/ )" << std::endl;
    std::cout << R"(  \___  (____  /__|_|  /\___  >  \____/ \_/  \___  >__|    )" << std::endl;
    std::cout << R"( /_____/     \/      \/     \/                   \/        )" << std::endl;
    std::cout << std::endl;

}
/*

#include "../include/card_factory.hpp"
#include <iostream>
#include <string>

int main() {

    CardFactory x;
    std::vector<Card *> y = x.createSuit(QUEEN);
    std::vector<std::string> z = y.at(0)->getArt();

    for (int i = 0; i < z.size(); i++) {
        // std::cout << z.at(i);
    }

}
*/
