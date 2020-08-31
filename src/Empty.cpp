//
// Created by penguin_ib on 5/8/19.
//

#include "Empty.h"
#include "Tile.h"
#include "GameBin.h"
#include <ncurses.h>
#include <iostream>

Empty::Empty() {
    owner = '*';
}

Empty::~Empty() {
    for (auto &i : edges) GameBin::toDeleteEdges.insert(i);
}

Empty::Empty(const char owner, unsigned long posX, unsigned long posY) : Tile(owner, posX, posY) {}

bool Empty::isSpawner() const { return false; }

void Empty::show() const { addch(EMPTY); }

bool Empty::isWall() const { return false; }

bool Empty::isUnit() const { return false; }