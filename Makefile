CC=g++

# C++ compilation flags, be sure it's set to C++17 and optimized
CFLAGS=-O3 -std=c++20

# linker flags, will link the SFML library
LDFLAGS=-O3 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# include directory(s), will include the engine files
INCLUDES=-I./src

# the source files for the ecs game engine
SRC_SFMLGAME=$(wildcard src/*.cpp) 
OBJ_SFMLGAME=$(SRC_SFMLGAME:.cpp=.o)

# all of these targets will be made if you just type make
all:sfmlgame

# define the main executable requirements / command
sfmlgame:$(OBJ_SFMLGAME) Makefile
	$(CC) $(OBJ_SFMLGAME) -o ./bin/$@ $(LDFLAGS)

.cpp.o:
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_SFMLGAME) ./bin/sfmlgame