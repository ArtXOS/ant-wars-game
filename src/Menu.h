//
// Created by penguin_ib on 5/20/19.
//

#ifndef SEMESTRALKA_MENU_H
#define SEMESTRALKA_MENU_H

#include "FileSystem.h"
#include <ncurses.h>
#include <iostream>

class FS;
/**
 * Enumeration of Menu states
 */
enum MenuState {
    MainMenu, ChooseNewGame, ChooseMap, ChooseSave, QuitAndSave, CreateSave, SessionEnd
};

/**
 * Class Menu helps to interact with a User
 */
class Menu {
public:

    /**
     * Default Menu constructor
     */
    Menu() = default;

    static bool withUser; ///< is true, when the Game is played by User and Bots, false - when played only by Bots
    static bool newGame; ///< is, true when the new Game is started, false - when the Game was created from the save
    static std::string saveFile; ///< contains name of the save file, from which th Game was created
    static std::string mapFile; ///< contains name of the map file, from which th Game was created
    static MenuState state; ///< represents current Menu state

    /**
     * Shows Main Menu. Here you can start new Game or load it from the save file
     */
    void showMenu() const;

    /**
     * Shows you a list of save files in the directory. You can choose each one
     */
    void savesMenu() const;

    /**
     * Shows you a list of map files in the directory. You can choose each one
     */
    void mapsMenu() const;

    /**
     * Showes quite menu during the Game process. You can quit from the Game, continue it or create a save
     */
    void quitMenu() const;

    /**
     * This method is used to interact with a user during the game process. Is always printed in the bottom of the map
     * Provides you an input line to make Moves or exit the Game
     * @return returns true, if all input data was correct, false - if there were mistakes
     */
    bool printMapMenu() const;
};


#endif //SEMESTRALKA_MENU_H
