//
// Created by penguin_ib on 5/8/19.
//

#include "Game.h"
#include "User.h"
#include <ncurses.h>
#include <unistd.h>

GameState Game::state;
Map *Game::gameMap = nullptr;

Game::Game(std::vector<Player *> &players) { this->players = players; }

Game::~Game() {
    if (!moves.empty()) for (auto &i : moves) GameBin::toDeleteMoves.insert(i);
}

void Game::executingLoop() {

    Game::state = GameState::UserTurn;
    GameBin::game->giveInfoAboutSpawners();
    bool end = false;
    int count = 1;

    while (!end) {

        switch (Game::state) {

            case GameState::UserTurn: {

                if (GameBin::game->checkPlayerSpawners()) {
                    Game::state = GameState::Winner;
                    continue;
                }

                if (players.at(0)->isTowersEmpty() && Menu::withUser) {
                    Game::state = GameState::Winner;
                    continue;
                }

                if (!Menu::withUser) {
                    Game::state = GameState::OtherPlayersTurns;
                    continue;
                }

                if (GameBin::state == GameBinState::GameEnd) {
                    end = true;
                    break;
                }

                if (!GameBin::menu->printMapMenu()) continue;

                count++;
                if ((unsigned long) count >= players.at(0)->getTowersCount() + 1 &&
                    GameBin::state != GameBinState::GameEnd) {
                    count = 1;
                    Game::state = GameState::OtherPlayersTurns;
                }
                else if (GameBin::state == GameBinState::GameEnd) {
                    count = 1;
                    Game::state = GameState::Exit;
                }
                else { Game::state = GameState::UserTurn; }

                break;
            }

            case GameState::OtherPlayersTurns: {

                GameBin::menu->printMapMenu();
                if (GameBin::state == GameBinState::GameEnd) break;

                for (auto &i : players) {
                    Move *tmp;
                    if (i == *players.begin() && Menu::withUser) continue;
                    for (unsigned long b = 0; b < i->getTowersCount(); b++) {
                        tmp = i->makeMove();
                        if (tmp != nullptr) moves.emplace_back(tmp);
                    }
                }

                usleep(25000);
                clear();
                if (moves.empty()) Game::state = GameState::Update;
                else Game::state = GameState::Animation;
                break;
            }
            case GameState::Animation: {

                bool finished = true;

                for (auto &i : moves) {

                    i->doChanges();

                    if (i->getState() == MoveState::Finished) continue;
                    else finished = false;

                }

                gameMap->printMap();
                refresh();
                usleep(30000);
                clear();

                if (finished) {
                    Game::state = GameState::Update;
                    continue;
                }
                else {
                    Game::state = GameState::Animation;
                    continue;
                }
            }

            case GameState::Update: {

                if (!moves.empty()) {
                    for (auto &i : moves) GameBin::toDeleteMoves.insert(i);
                    moves.clear();
                }

                for (auto &i : Game::gameMap->getSpawners()) {
                    unsigned long posY, posX;
                    posY = i->getPosY();
                    posX = i->getPosX();
                    for (auto x = -2; x <= 2; x++) {
                        for (auto y = -2; y <= 2; y++) {
                            ((Tower *) (Game::gameMap->getTiles().at(posY + y).at(posX + x)))->updateUnitCount(false);
                        }
                    }

                }

                gameMap->updateNodes();
                Game::state = GameState::UserTurn;
                break;
            }

            case GameState::Winner: {

                gameMap->printMap();

                if (Menu::withUser && players.at(0)->isTowersEmpty()) {
                    addstr(" YOU ARE LOSER!!!");
                } else {
                    for (auto i : players) {
                        if (i->getTowersCount() > 0) {
                            addch((unsigned char) i->getID());
                            addstr(" IS WINNER!!!");
                        }
                    }
                }

                refresh();
                usleep(3000000);
                clear();

                Menu::state = MenuState::MainMenu;
                GameBin::state = GameBinState::GameEnd;
                end = true;
                break;
            }

            case GameState::Exit: {
                GameBin::state = GameBinState::GameEnd;
                end = true;
                break;
            }

            default:
                break;
        }

    }

}

void Game::giveInfoAboutSpawners() const {
    gameMap->sendSpawnerCores();
}

bool Game::userInputHandle() const {
    return players.front()->handleInput();
}

void Game::addMove(Move *move) {
    this->moves.emplace_back(move);
}

void Game::changeSpawnerOwner(const char previous, const char next, Tile *spawner) {
    for (auto &i : players) {
        if (i->getID() == previous && previous != 'N') i->removeSpawner(spawner);
        if (i->getID() == next) i->addSpawner(spawner);
        if (i->getID() == next && previous == i->getID()) {
            i->removeSpawner(spawner);
            i->addSpawner(spawner);
        }
    }
}

bool Game::checkPlayerSpawners() const {

    unsigned long all = players.size();
    unsigned long count = 0;
    for (auto &i : players) {
        if (i->isTowersEmpty()) ++count;
    }

    if (count == all - 1) {
        Game::state = GameState::Winner;
        return true;
    }
    else return false;

}

std::vector<Player *> &Game::getPlayers() {
    return players;
}