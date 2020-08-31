//
// Created by penguin_ib on 5/12/19.
//
#include "Wall.h"
#include "GameBin.h"
#include <iostream>
#include <ncurses.h>

Wall::Wall(const char owner, unsigned long posX, unsigned long posY) : Tile(owner, posX, posY) {}

Wall::~Wall() { for (auto &i : edges) GameBin::toDeleteEdges.insert(i); }

bool Wall::isSpawner() const { return false; }

bool Wall::isWall() const { return true; }

void Wall::show() const {
    attron(COLOR_PAIR(WALL_COLOR));
    addch(WALL);
    attroff(COLOR_PAIR(WALL_COLOR));
}