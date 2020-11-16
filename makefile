CFLAGS = -O
FLAGS = -std=c++20 -lstdc++ `pkg-config gtkmm-3.0 --cflags --libs`
CC = g++
EXECUTIBLE = GameSettings
INC = include/

GameSettings: main.o vdfParser.o
		$(CC) $(CFLAGS) -o $(EXECUTIBLE) main.o vdfParser.o $(FLAGS)

main.o: main.cpp
		$(CC) $(CFLAGS) -c main.cpp $(FLAGS)

vdfParser.o: $(INC)vdfParser/*
		$(CC) $(CFLAGS) -c $(INC)vdfParser/vdfParser.cpp $(FLAGS)

clean:
		rm -f *.o && rm GameSettings