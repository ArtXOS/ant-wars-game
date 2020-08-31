//
// Created by penguin_ib on 5/8/19.
//

#ifndef SEMESTRALKA_FILESYSTEM_H
#define SEMESTRALKA_FILESYSTEM_H

#include "Game.h"
#include "GameBin.h"
#include <string>
class Game;

/**
 * This exception is used in a case of an invalid format of a map or a save file
 */
class IllegalFileFormatException {
};

/**
 * The purpose of this class is to help work with a files: saves or maps
 */
class FS {
public:

    /**
     * Default constructor. Initialise saves directory with "./examples/saves", maps directory with "./examples/maps"
     */
    FS();

    /**
     * Default destructor
     */
    ~FS() = default;

    /**
     * Method isn't constant, because returned copy of a relative path modifies in other method of this class
     * @return returns a copy of a relative path to saves directory
     */
    std::string getSaveDir();

    /**
     * Method isn't constant, because returned copy of a relative path modifies in other method of this class
     * @return returns a copy of a relative path to maps directory
     */
    std::string getMapsDir();

    /**
     * Method opens a directory return file names in it
     * @param[in] directory - relative path to the directory
     * @return returns vector of strings with names of the files in the directory
     */
    std::vector<std::string> filesInDirectory(char *directory) const;

    /**
     * Reads map file and initialises GameBin::game and Game::gameMap
     * In case of a error throws IllegalFileFormatException
     * @param[in] srcFileName - name of the map file
     * @param[in] withUser - with real user - true, only bots - false
     */
    void readMap(const std::string &srcFileName, bool withUser) const;

    /**
     * Reads save file and initialises GameBin::game and Game::gameMap
     * In case of a error throws IllegalFileFormatException
     * @param[in] srcFileName - name of the save file
     */
    void loadSave(const std::string &srcFileName) const;

    /**
     * Creates save file in the saves directory
     * In case of a error throws IllegalFileFormatException
     * @param[in] name - name of the file, which will be created
     */
    void writeSave(const std::string &name) const;

    /**
     * Checks if the file already exists in the saves directory
     * In case of a error throws IllegalFileFormatException
     * @param[in] name - name of the file
     * @return false - file already exists, true - file doesn't exist
     */
    bool checkFileName(char *name);

private:
    std::string saveDir; ///<relative path to the directory with saves
    std::string mapsDir; ///<relative path to the directory with maps
};


#endif //SEMESTRALKA_FILESYSTEM_H
