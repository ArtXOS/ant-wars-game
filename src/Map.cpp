//
// Created by penguin_ib on 5/8/19.
//

#include "GameBin.h"
#include "Map.h"
#include "Empty.h"
#include "Player.h"
#include "Tower.h"
#include "Route.h"
#include "Wall.h"
#include <string>
#include <ncurses.h>
#include <iostream>
#include <functional>
#include <fstream>
#include <unistd.h>
#include <set>

int Map::width;
int Map::height;

Route *Map::route = nullptr;

Map::Map(int width, int height, const std::vector<Tower *> &spawners) : spawners(spawners) {
    Map::width = width;
    Map::height = height;
    std::vector<Tile *> tmpVector((unsigned long) Map::width);
    for (unsigned long i = 0; i < (unsigned long) width; i++) {
        tmpVector.at(i) = nullptr;
    }
    for (unsigned long i = 0; i < (unsigned long) height; i++) {
        tiles.push_back(tmpVector);
    }
}

Map::~Map() {
    for (auto &i : tiles) {
        for (auto &b : i) {
            GameBin::toDeleteTiles.insert(b);
        }
    }
    GameBin::toDeleteRoute.insert(route);
}

void Map::replaceTile(Tile *tile, unsigned long posX, unsigned long posY) {
    Tile *tmp = tiles.at(posY).at(posX);
    tiles.at(posY).at(posX) = tile;
    GameBin::toDeleteTiles.insert(tmp);
}

void Map::addSpawner(Tower *tile) { spawners.emplace_back(tile); }

void Map::sendSpawnerCores() { for (auto &i : GameBin::game->getPlayers()) i->recieveSpawners(spawners); }

void Map::recalculateTiles() {

    for (unsigned long posY = 0; posY < (unsigned long) Map::height; posY++) {
        for (unsigned long posX = 0; posX < (unsigned long) Map::width; posX++) {

            if (!tiles.at(posY).at(posX)->isSpawner()) continue;

            char owner = tiles.at(posY).at(posX)->getOwner();
            auto core = tiles.at(posY).at(posX);

            char name = core->getName();

            char tmp[9] = "seuvzbqx";
            int counter = 0;
            for (auto x = -2; x <= 2; x++) {
                for (auto y = -2; y <= 2; y++) {
                    if (x == 0 && y == 0) continue;
                    else if (x != -2 && x != 2 && y != 2 && y != -2) {
                        this->replaceTile(new Tower(owner, posX + x, posY + y, name, core), posX + x, posY + y);
                        tiles.at(posY + y).at(posX + x)->setPart(tmp[counter]);
                        counter++;
                    } else {
                        this->replaceTile(new Tower(owner, posX + x, posY + y, name, core), posX + x, posY + y);
                        tiles.at(posY + y).at(posX + x)->setPart('w');
                    }
                }
            }
        }
    }
}

void Map::printMap() const {
    for (auto &i : tiles) {
        for (auto &b : i) {
            b->show();
        }
        addch('\n');
        addch('\r');
    }

}

void Map::createRoute() const { Map::route = new Route(tiles, spawners); }

std::vector<Tower *> &Map::getSpawners() { return spawners; }

std::vector<std::vector<Tile *> > &Map::getTiles() { return tiles; }

void Map::updateNodes() {

    for (unsigned long posY = 0; posY < (unsigned long) Map::height; posY++) {
        for (unsigned long posX = 0; posX < (unsigned long) Map::width; posX++) {

            if (tiles.at(posY).at(posX)->isWall()) continue;

            tiles.at(posY).at(posX)->deleteEdges();

            for (auto y = -1; y <= 1; y++) {
                for (auto x = -1; x <= 1; x++) {
                    if (tiles.at(posY + y).at(posX + x)->isWall()) continue;
                    if (x != 0 && y != 0) tiles.at(posY).at(posX)->addEdge(tiles.at(posY + y).at(posX + x));
                    else if (x == 0 && y != 0) tiles.at(posY).at(posX)->addEdge(tiles.at(posY + y).at(posX + x));
                    else if (x != 0) tiles.at(posY).at(posX)->addEdge(tiles.at(posY + y).at(posX + x));
                }
            }
        }
    }
}

void Map::readTilesFromFile(std::ifstream &filein, const std::map<char, char> &towersOwners) {
    char tmp;

    filein.get(tmp);
    filein.get(tmp);

    for (unsigned long i = 0; i < (unsigned long) height; i++) {
        for (unsigned long j = 0; j < (unsigned long) width; j++) {

            filein.get(tmp);

            switch (tmp) {
                case 32:
                    replaceTile(new Empty('*', j, i), j, i);
                    break;
                case '#':
                    replaceTile(new Wall('N', j, i), j, i);
                    break;
                case '*':
                    replaceTile(new Tower('N', j, i), j, i);
                    break;
                case '$':
                    replaceTile(new Tower('N', j, i), j, i);
                    break;
                default:
                    Tower *spawner = new Tower(towersOwners.find(tmp)->second, j, i, tmp);
                    spawner->setPart('c');
                    replaceTile(spawner, j, i);
                    addSpawner(spawner);
                    break;
            }
        }

        filein.get(tmp);
    }

    for (unsigned long i = 0; i < (unsigned long) width; i++) {
        if (!tiles.at(0).at(i)->isWall()) {
            for (auto &i : tiles) for (auto &b : i) { GameBin::toDeleteTiles.insert(b); }
            throw IllegalFileFormatException();
        }
        if (!tiles.at((unsigned long) height - 1).at(i)->isWall()) {
            for (auto &i : tiles) for (auto &b : i) { GameBin::toDeleteTiles.insert(b); }
            throw IllegalFileFormatException();
        }
    }

    for (unsigned long i = 0; i < (unsigned long) height; i++) {
        if (!tiles.at(i).at(0)->isWall()) {
            for (auto &i : tiles) for (auto &b : i) { GameBin::toDeleteTiles.insert(b); }
            throw IllegalFileFormatException();
        }
        if (!tiles.at(i).at((unsigned long) width - 1)->isWall()) {
            for (auto &i : tiles) for (auto &b : i) { GameBin::toDeleteTiles.insert(b); }
            throw IllegalFileFormatException();
        }
    }
}

bool Map::updateSpawnerAfterLoad(const char name, const char owner, int units, int level) {

    bool done = false;
    for (auto i : spawners) {
        if (i->getName() != name) continue;
        done = true;
        i->updateAfterSave(owner, units, level);
        for (auto &b : GameBin::game->getPlayers()) { if (b->getID() == owner) b->addSpawner(i); }
    }

    if (!done) {
        for (auto &i : spawners) GameBin::toDeleteTiles.insert(i);
        throw IllegalFileFormatException();
    }

    return done;
}


