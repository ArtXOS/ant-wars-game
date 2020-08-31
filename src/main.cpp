#include "Map.h"
#include "Empty.h"
#include "Game.h"
#include "GameBin.h"
#include "FileSystem.h"
#include "Menu.h"
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <map>
#include <set>
#include <functional>
#include <math.h>
#include <algorithm>
#include <string>
#include <array>
#include <chrono>
#include <ctime>
#include <ncurses.h>
#include <unistd.h>


/**
 * @mainpage AntWars
 *
 * This is a simple game engine for turn-based strategy game.
 * The setting is Ant Wars, where Ant colonies fight against
 * each other.
 *
 * Your have to defeat all your enemies to win!
 * You have a possibility to create your own mapes in the special format,
 * and also do saves during the game.
 *
 * Max amount of players is 4. You can watch how Bots fight against each other
 * or be the part of this war.
 *
 */



int main() {

    if (LEVEL != 1 && LEVEL != 0) return 0;

    srand((unsigned long) time(NULL));

    FS *fileSystem = new FS();
    Game *game = nullptr;
    Menu *menu = new Menu();
    GameBin *bin = new GameBin();

    GameBin::game = game;
    GameBin::menu = menu;
    GameBin::fileSystem = fileSystem;

    ///>In the end of a session all data will be deleted
    if (bin->start()) {
        delete menu;
        delete fileSystem; /*bin->deleteData();*/ delete bin;
        return 0;
    } else {
        bin->deleteData();
        delete menu;
        delete fileSystem;
        delete bin;
        return 1;
    }
}



