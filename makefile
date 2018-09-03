blackjack.out: bin/card.o bin/deck.o bin/game.o bin/player.o bin/main.o
	g++ -g -Wall -O2 bin/card.o bin/deck.o bin/game.o bin/player.o bin/main.o -o blackjack.out

bin/card.o: src/card/card.cpp src/card/card.hpp
	g++ -g -Wall -O2 -c src/card/card.cpp -o bin/card.o
bin/deck.o: src/deck/deck.cpp src/deck/deck.hpp
	g++ -g -Wall -O2 -c src/deck/deck.cpp -o bin/deck.o
bin/game.o: src/game/game.cpp src/game/game.hpp
	g++ -g -Wall -O2 -c src/game/game.cpp -o bin/game.o
bin/player.o: src/player/player.cpp src/player/player.hpp
	g++ -g -Wall -O2 -c src/player/player.cpp -o bin/player.o
bin/main.o: src/main.cpp
	g++ -g -Wall -O2 -c src/main.cpp -o bin/main.o

clean:
	rm bin/*.o blackjack.out
