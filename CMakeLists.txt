cmake_minimum_required(VERSION 3.12)
project(asciijack)

set(CMAKE_CXX_STANDARD 17)

add_executable(asciijack src/main.cpp src/card/card.cpp src/card/card.hpp src/deck/deck.cpp src/deck/deck.hpp src/game/game.cpp src/game/game.hpp src/player/player.cpp src/player/player.cpp)
