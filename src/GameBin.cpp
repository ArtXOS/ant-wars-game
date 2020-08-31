//
// Created by penguin_ib on 5/12/19.
//

#include "GameBin.h"
#include "Menu.h"
#include "Game.h"
#include "FileSystem.h"
#include <unistd.h>

Menu *GameBin::menu = nullptr;
Game *GameBin::game = nullptr;
FS *GameBin::fileSystem = nullptr;

GameBinState GameBin::state;

std::set<Tile *> GameBin::toDeleteTiles;
std::set<Edge *> GameBin::toDeleteEdges;
std::set<Move *> GameBin::toDeleteMoves;
std::set<Player *> GameBin::toDeletePlayers;
std::set<Route *> GameBin::toDeleteRoute;
std::set<Game *> GameBin::toDeleteGame;

bool GameBin::start() {
    return this->gameLoop();
}

void GameBin::deleteData() {
    if (!toDeleteGame.empty()) { for (auto &i : toDeleteGame) delete i; }
    if (!toDeleteMoves.empty()) { for (auto &i : toDeleteMoves) delete i; }
    if (!toDeleteTiles.empty()) { for (auto &i : toDeleteTiles) delete i; }
    if (!toDeleteEdges.empty()) { for (auto &i : toDeleteEdges) delete i; }
    if (!toDeleteRoute.empty()) { for (auto &i : toDeleteRoute) delete i; }
    toDeleteTiles.clear();
    toDeleteMoves.clear();
    toDeleteEdges.clear();
    toDeleteRoute.clear();
    toDeleteGame.clear();
}

void GameBin::deletePlayers() {
    if (!toDeletePlayers.empty()) { for (auto &i : toDeletePlayers) delete i; }
    toDeletePlayers.clear();
}

bool GameBin::gameLoop() {
    initscr();
    curs_set(0);

    GameBin::state = GameBinState::GameMenu;

    while (true) {
        switch (GameBin::state) {

            case GameBinState::GameMenu: {
                menu->showMenu();
                break;
            }

            case GameBinState::GameProcess: {
                try {
                    if (Menu::newGame) {
                        fileSystem->readMap(GameBin::fileSystem->getMapsDir().append("/").append(Menu::mapFile),
                                            Menu::withUser);
                        state = GameBinState::GameProcess;
                    } else {
                        fileSystem->loadSave(GameBin::fileSystem->getSaveDir().append("/").append(Menu::saveFile));
                        state = GameBinState::GameProcess;
                    }
                }
                catch (IllegalFileFormatException) {
                    clear();
                    refresh();
                    move(5, 25);
                    refresh();
                    addstr("File is corrupted!");
                    refresh();
                    usleep(500000);
                    GameBin::state = GameBinState::GameMenu;
                    GameBin::toDeleteGame.insert(GameBin::game);
                    delete Game::gameMap;
                    break;
                }

                try {
                    GameBin::game->executingLoop();
                }
                catch (std::exception &) {
                    clear();
                    refresh();
                    move(5, 25);
                    refresh();
                    addstr("Something went wrong ;( Sorry");
                    refresh();
                    usleep(1500000);
                    GameBin::state = GameBinState::GameEnd;
                    break;
                }

                break;
            }

            case GameBinState::GameEnd: {
                delete Game::gameMap;
                Game::gameMap = nullptr;
                GameBin::toDeleteGame.insert(GameBin::game);
                menu->showMenu();
                if (Menu::state == MenuState::ChooseSave || Menu::state == MenuState::ChooseMap)
                    GameBin::state = GameBinState::GameProcess;
                break;
            }

            case GameBinState::End: {
                deleteData();
                deletePlayers();
                clear();
                refresh();
                endwin();
                return true;
            }
        }
    }
}

