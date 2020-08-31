PROGRAM=bryloill

CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -Wextra -g -Wno-long-long -O0 -ggdb

all: compile doc

run: compile
	./$(PROGRAM)

compile: $(PROGRAM)

doc: src/main.cpp src/Map.h src/Tile.h src/Unit.h src/Empty.h src/Game.h src/FileSystem.h src/Player.h src/GameBin.h src/Wall.h src/Tower.h src/Move.h src/User.h src/Bot.h src/Route.h src/Menu.h
	doxygen Doxyfile

$(PROGRAM): objs/main.o objs/Map.o objs/Tile.o objs/Unit.o objs/Empty.o objs/Game.o objs/FileSystem.o objs/Player.o objs/GameBin.o objs/Wall.o objs/Tower.o objs/Move.o objs/User.o objs/Bot.o objs/Route.o objs/Menu.o

	$(CC) $(CFLAGS) $^ -o $@ -lncurses
	
objs/Bot.o: src/Bot.cpp src/Bot.h src/Player.h src/Tile.h src/Tower.h \
 src/Move.h src/Route.h src/Unit.h src/Map.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Empty.o: src/Empty.cpp src/Empty.h src/Tile.h src/GameBin.h \
 src/FileSystem.h src/Game.h src/Map.h src/Route.h src/Tower.h \
 src/Player.h src/Move.h src/Unit.h src/Menu.h
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/FileSystem.o: src/FileSystem.cpp src/Map.h src/Route.h src/Tile.h \
 src/Tower.h src/Player.h src/Move.h src/Unit.h src/Empty.h src/Game.h \
 src/GameBin.h src/FileSystem.h src/Menu.h src/Wall.h src/User.h \
 src/Bot.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/GameBin.o: src/GameBin.cpp src/FileSystem.h src/Game.h src/Map.h \
 src/Route.h src/Tile.h src/Tower.h src/Player.h src/Move.h src/Unit.h \
 src/GameBin.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Game.o: src/Game.cpp src/Game.h src/Map.h src/Route.h src/Tile.h \
 src/Tower.h src/Player.h src/Move.h src/Unit.h src/GameBin.h \
 src/FileSystem.h src/Menu.h src/User.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/main.o: src/main.cpp src/Map.h src/Route.h src/Tile.h src/Tower.h \
 src/Player.h src/Move.h src/Unit.h src/Empty.h src/Game.h src/GameBin.h \
 src/FileSystem.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Map.o: src/Map.cpp src/GameBin.h src/FileSystem.h src/Game.h src/Map.h \
 src/Route.h src/Tile.h src/Tower.h src/Player.h src/Move.h src/Unit.h \
 src/Menu.h src/Empty.h src/Wall.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Menu.o: src/Menu.cpp src/Menu.h src/FileSystem.h src/Game.h src/Map.h \
 src/Route.h src/Tile.h src/Tower.h src/Player.h src/Move.h src/Unit.h \
 src/GameBin.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Move.o: src/Move.cpp src/Empty.h src/Tile.h src/Move.h src/Player.h \
 src/Tower.h src/Map.h src/Route.h src/Unit.h src/Game.h src/GameBin.h \
 src/FileSystem.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Player.o: src/Player.cpp src/Player.h src/Tile.h src/Tower.h src/Move.h \
 src/Route.h src/Unit.h src/Map.h src/Menu.h src/FileSystem.h src/Game.h \
 src/GameBin.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Route.o: src/Route.cpp src/Route.h src/Tile.h src/Tower.h src/GameBin.h \
 src/FileSystem.h src/Game.h src/Map.h src/Player.h src/Move.h src/Unit.h \
 src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses	
objs/Tile.o: src/Tile.cpp src/Tile.h src/Map.h src/Route.h src/Tower.h \
 src/Player.h src/Move.h src/Unit.h src/GameBin.h src/FileSystem.h \
 src/Game.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Tower.o: src/Tower.cpp src/Tower.h src/Tile.h src/Game.h src/Map.h \
 src/Route.h src/Player.h src/Move.h src/Unit.h src/GameBin.h \
 src/FileSystem.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Unit.o: src/Unit.cpp src/Unit.h src/Map.h src/Route.h src/Tile.h \
 src/Tower.h src/Player.h src/Move.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/User.o: src/User.cpp src/User.h src/Player.h src/Tile.h src/Tower.h \
 src/Move.h src/Route.h src/Unit.h src/Map.h src/GameBin.h \
 src/FileSystem.h src/Game.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses
objs/Wall.o: src/Wall.cpp src/Wall.h src/Tile.h src/GameBin.h src/FileSystem.h \
 src/Game.h src/Map.h src/Route.h src/Tower.h src/Player.h src/Move.h \
 src/Unit.h src/Menu.h | objs
	$(CC) $(CFLAGS) -c $< -o $@ -lncurses

objs: 
	mkdir objs
	
clean:
	rm -rf $(PROGRAM) objs/ doc/ 2>/dev/null

