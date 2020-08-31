//
// Created by penguin_ib on 5/8/19.
//

#include "Tile.h"
#include "Map.h"
#include "GameBin.h"
#include <ncurses.h>

void Tile::addLevel() {}

void Tile::minusForUpgrade() {}

Tile::Tile(const char owner, unsigned long posX, unsigned long posY) : owner(owner), posX(posX),
                                                                       posY(posY) { initColors(); }

Tile::~Tile() { if (!edges.empty())for (auto &i : edges) GameBin::toDeleteEdges.insert(i); }

unsigned long Tile::getPosX() const { return posX; }

unsigned long Tile::getPosY() const { return posY; }

char Tile::getOwner() const { return owner; }

void Tile::setOwner(const char newOwner) { owner = newOwner; }

bool Tile::isSpawner() const { return false; }

bool Tile::isWall() const { return false; }

void Tile::addEdge(Tile *to) { edges.emplace_back(new Edge(this, to)); }

void Tile::receiveAttack(Tile*) {}

void Tile::minusUnits() {}

void Tile::plusForAttack() {}

void Tile::minusForAttack() {}

void Tile::setLevel(int level) { level = level;}

void Tile::setUCount(int count) { count = count; }

void Tile::updateOwner(const char) {}

int Tile::getUCount() const { return 0; }

bool Tile::isUnit() const { return false; }

void Tile::setPart(const char) {}

void Tile::show() const {}

Tile *Tile::getCore() const { return nullptr; }

char Tile::getName() const { return ' '; }

void Tile::deleteEdges() {
    for (auto &i : edges) { GameBin::toDeleteEdges.insert(i); }
    edges.clear();
}

Edge::Edge(Tile *from, Tile *to) : from(from), to(to) {}

Tile *Edge::getTo() { return to; }

void initColors() {
    start_color();
    init_pair(A_PLAYER, COLOR_RED, COLOR_BLACK);
    init_pair(B_PLAYER, COLOR_BLUE, COLOR_BLACK);
    init_pair(C_PLAYER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(D_PLAYER, COLOR_GREEN, COLOR_BLACK);
    init_pair(N_PLAYER, COLOR_WHITE, COLOR_BLACK);
    init_pair(WALL_COLOR, COLOR_WHITE, COLOR_BLACK);
    init_pair(CORE_COLOR, COLOR_CYAN, COLOR_BLACK);
    init_pair(A_PLAYER_WALL, COLOR_RED, COLOR_RED);
    init_pair(B_PLAYER_WALL, COLOR_BLUE, COLOR_BLUE);
    init_pair(C_PLAYER_WALL, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(D_PLAYER_WALL, COLOR_GREEN, COLOR_GREEN);
    init_pair(N_PLAYER_WALL, COLOR_WHITE, COLOR_WHITE);
}
