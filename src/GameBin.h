//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_GAMEBIN_H
#define SEMESTRALKA_GAMEBIN_H


#include "FileSystem.h"
#include "Menu.h"
#include "Game.h"
#include <ncurses.h>

class Menu;
class Game;
class FS;

/**
 * Enumeration of GameBin states
 */
enum GameBinState {
    GameMenu, GameProcess, GameEnd, End
};

/**
 * Contains every part of a program: Menu, FileSystem, Game. Rules every processes in the program
 */
class GameBin {
public:

    /**
     * Default constructor of a GameBin
     */
    GameBin() = default;

    static GameBinState state; ///<Contains current GameBin state
    static Game *game; ///<Contains pointer to a current Game
    static Menu *menu; ///<Contains pointer to Menu
    static FS *fileSystem; ///<Contains pointer to a FileSystem FS
    static std::set<Tile *> toDeleteTiles; ///<Contains pointers to Tiles, which will be freed in the end of a session
    static std::set<Edge *> toDeleteEdges; ///<Contains pointers to Edges, which will be freed in the end of a session
    static std::set<Move *> toDeleteMoves; ///<Contains pointers to Moves, which will be freed in the end of a session
    static std::set<Player *> toDeletePlayers; ///<Contains pointers to Players, which will be freed in the end of a session
    static std::set<Route *> toDeleteRoute; ///<Contains pointers to Routes, which will be freed in the end of a session
    static std::set<Game *> toDeleteGame; ///<Contains pointers to Games, which will be freed in the end of a session

    /**
     * Starts executing loop
     * @return returns true - if there weren't any errors during the game execution process, false - in case of an error
     */
    bool start();

    /**
     * Clear contents of a static sets after the end of an each session
     */
    void deleteData();

private:
    /**
     * Program loop. Controls every process in the program
     * Switches between different GameBin states
     * @return returns true - if there weren't any errors during the game execution process, false - in case of an error
     */
    bool gameLoop();

    /**
     * Frees Player pointers in the static set of Player* "playersToDelete"
     */
    void deletePlayers();
};


#endif //SEMESTRALKA_GAMEBIN_H
