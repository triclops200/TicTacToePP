tictactoe: Main.o Player.o
	g++ -DNCURSES_STATIC Main.o Player.o -O2 -otictactoe -lncurses
Main.o: Main.cpp
	g++ -c Main.cpp -oMain.o
Player.o: Player.cpp Player.hpp
	g++ -c Player.cpp Player.hpp 
all: tictactoe

clean:
	rm -rf *.o tictactoe
