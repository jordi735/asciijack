bin/asciijack: bin/card.o bin/deck.o bin/game.o bin/player.o bin/main.o bin/card_factory.o bin/ascii.o
	g++ bin/*.o -O2 -o bin/asciijack

bin/card.o: src/card.cpp include/card.hpp
	g++ -c -O2 src/card.cpp -o bin/card.o
bin/deck.o: src/deck.cpp include/deck.hpp
	g++ -c -O2 src/deck.cpp -o bin/deck.o
bin/game.o: src/game.cpp include/game.hpp
	g++ -c -O2 src/game.cpp -o bin/game.o
bin/player.o: src/player.cpp include/player.hpp
	g++ -c -O2 src/player.cpp -o bin/player.o
bin/card_factory.o: src/card_factory.cpp include/card_factory.hpp
	g++ -c -O2 src/card_factory.cpp -o bin/card_factory.o
bin/ascii.o: resources/ascii.cpp resources/ascii.hpp
	g++ -c -O2 resources/ascii.cpp -o bin/ascii.o
bin/main.o: src/main.cpp
	g++ -c -O2 src/main.cpp -o bin/main.o

clean:
	rm bin/*
