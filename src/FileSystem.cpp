//
// Created by penguin_ib on 5/8/19.
//
#include "Map.h"
#include "Empty.h"
#include "Game.h"
#include "GameBin.h"
#include "FileSystem.h"
#include "Menu.h"
#include "FileSystem.h"
#include "Game.h"
#include "Empty.h"
#include "Wall.h"
#include "Tower.h"
#include "Player.h"
#include "User.h"
#include "Bot.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <dirent.h>
#include <algorithm>
#include <cstring>
#include <unistd.h>

FS::FS() {
    this->saveDir = "./examples/saves";
    this->mapsDir = "./examples/maps";
}

std::string FS::getSaveDir() { return saveDir; }

std::string FS::getMapsDir() { return mapsDir; }

void FS::readMap(const std::string &srcFileName, bool withUser) const {
    Game::gameMap = nullptr;

    std::ifstream filein(srcFileName, std::ios::binary | std::ios::in);
    if (filein.fail() || !filein.is_open()) { throw IllegalFileFormatException(); }

    int playersTowers, towers, width, height;
    char tmp, player, tower;
    std::map<char, char> towersOwners;

    filein >> playersTowers >> tmp >> towers >> tmp >> width >> tmp >> height >> tmp;
    if (playersTowers > towers || towers < 2 || width <= 0 || height <= 0 || width > 150 ||
        height > 70) { throw IllegalFileFormatException(); }

    std::vector<Player *> players;
    std::vector<Tower *> spawners;

    int count = 0;
    std::map<char, bool> createdPLayers = {{'A', false},
                                           {'B', false},
                                           {'C', false},
                                           {'D', false}};

    while (count < towers) {

        filein >> tower >> tmp >> player >> tmp;

        player = (char) toupper(player);
        tower = (char) toupper(tower);

        if (count == towers - 1) { if (tmp != ';') throw IllegalFileFormatException(); }

        switch (player) {

            case 'A':
                if (!createdPLayers.find(player)->second && withUser) {
                    createdPLayers.find(player)->second = true;
                    players.emplace_back(new User(player));
                } else if (!createdPLayers.find(player)->second) {
                    createdPLayers.find(player)->second = true;
                    if (!LEVEL)players.emplace_back(new RandomBot(player));
                    else players.emplace_back(new PriorityBot(player));
                }
                break;
            case 'B':
                if (!createdPLayers.find(player)->second) {
                    createdPLayers.find(player)->second = true;
                    if (!LEVEL)players.emplace_back(new RandomBot(player));
                    else players.emplace_back(new PriorityBot(player));
                }
                break;
            case 'C':
                if (!createdPLayers.find(player)->second) {
                    createdPLayers.find(player)->second = true;
                    if (!LEVEL)players.emplace_back(new RandomBot(player));
                    else players.emplace_back(new PriorityBot(player));
                }
                break;
            case 'D':
                if (!createdPLayers.find(player)->second) {
                    if (!LEVEL)players.emplace_back(new RandomBot(player));
                    else players.emplace_back(new PriorityBot(player));
                }
                break;
            case 'N':
                break;
            default:
                throw IllegalFileFormatException();
        }

        towersOwners.insert(std::pair<char, char>(tower, player));
        count++;

    }

    for (auto &i : players) { GameBin::toDeletePlayers.insert(i); }
    for (auto &i : spawners) { GameBin::toDeleteTiles.insert(i); }

    Map *gameMap = new Map(width, height, spawners);
    Game::gameMap = gameMap;

    gameMap->readTilesFromFile(filein, towersOwners);

    if (gameMap->getSpawners().size() != (unsigned long) towers) {
        delete Game::gameMap;
        for (auto &i : players) GameBin::toDeletePlayers.insert(i);
        for (auto &i : spawners) GameBin::toDeleteTiles.insert(i);
        for (auto &i : gameMap->getTiles()) for (auto &b : i) { GameBin::toDeleteTiles.insert(b); }
        throw IllegalFileFormatException();
    }

    filein.close();

    gameMap->recalculateTiles();
    gameMap->updateNodes();
    gameMap->createRoute();

    GameBin::game = new Game(players);

}


void FS::loadSave(const std::string &srcFileName) const {

    Game::gameMap = nullptr;

    std::ifstream filein(srcFileName, std::ios::binary | std::ios::in);
    if (filein.fail() || !filein.is_open()) throw IllegalFileFormatException();

    char tmp;
    bool withPlayer;
    std::string name;

    filein >> withPlayer;
    if (withPlayer != 1 && withPlayer != 0) throw IllegalFileFormatException();

    filein >> name;

    Menu::withUser = withPlayer;
    Menu::mapFile = name;

    readMap(GameBin::fileSystem->getMapsDir().append("/").append(Menu::mapFile), Menu::withUser);

    for (auto &i : GameBin::game->getPlayers()) i->erasePlayerTowers();

    for (unsigned long i = 0; i < Game::gameMap->getSpawners().size(); i++) {
        char tower, owner;
        int units, level;
        filein >> tower >> tmp >> owner >> tmp >> units >> tmp >> level >> tmp;
        if (tmp != ';') throw IllegalFileFormatException();
        Game::gameMap->updateSpawnerAfterLoad(tower, owner, units, level);
    }
}


void FS::writeSave(const std::string &str) const {

    std::ofstream fileout(GameBin::fileSystem->getSaveDir().append("/").append(str).append(".txt").c_str(),
                          std::ios::binary | std::ios::out);

    if (fileout.fail() || !fileout.is_open()) throw IllegalFileFormatException();

    fileout << (int) Menu::withUser << std::endl;
    fileout << Menu::mapFile << std::endl;

    for (auto &i : Game::gameMap->getSpawners()) {
        fileout << i->getName() << '-' << i->getOwner() << ':' << i->getUCount() << ':' << i->getLevel() << ';'
                << std::endl;
    }
}

std::vector<std::string> FS::filesInDirectory(char *directory) const {

    std::vector<std::string> files;
    DIR *dir;
    struct dirent *f = nullptr;
    dir = opendir(directory);

    while (dir) {
        f = readdir(dir);
        if (!f) break;
        if (f->d_type != DT_REG) continue;
        files.emplace_back(std::string(f->d_name));
    }

    delete f;
    closedir(dir);
    sort(files.begin(), files.end());
    return files;
}

bool FS::checkFileName(char *str) {

    char directory[17];
    strcpy(directory, this->getSaveDir().c_str());

    std::vector<std::string> files;
    DIR *dir;
    struct dirent *f = nullptr;
    dir = opendir(directory);

    while (dir) {
        f = readdir(dir);
        if (!f) break;
        if (f->d_type != DT_REG) continue;
        if (strcmp(f->d_name, str) == 0) return false;
    }

    closedir(dir);
    delete f;
    return true;
}
