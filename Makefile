all:
	mkdir -p bin
	mkdir -p obj/src
	g++  -g -O2 -std=c++11 -Iinclude -Isrc -c main.cpp -o obj/main.o
	g++  -g -O2 -std=c++11 -Iinclude -Isrc -c src/Bot.cpp -o obj/src/Bot.o
	g++  -g -O2 -std=c++11 -Iinclude -Isrc -c src/Game.cpp -o obj/src/Game.o
	g++  -g -O2 -std=c++11 -Iinclude -Isrc -c src/Timer.cpp -o obj/src/Timer.o
	g++  -o bin/lightridersGame obj/main.o obj/src/Bot.o obj/src/Game.o obj/src/Timer.o  -lsfml-graphics -lsfml-window -lsfml-system
.PHONY: clean
clean:
	rm -rf bin/*
	rm -rf obj