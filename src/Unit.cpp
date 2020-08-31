//
// Created by penguin_ib on 5/8/19.
//

#include "Unit.h"
#include <unistd.h>
#include <ncurses.h>

Unit::Unit(const char owner, unsigned long posX, unsigned long posY) : Tile(owner, posX, posY) {
    this->life = 1;
    this->index = 0;
}

bool Unit::isSpawner() const { return false; }

void Unit::show() const {
    switch (this->getOwner()) {
        case 'A':
            attron(COLOR_PAIR(A_PLAYER));
            addch((unsigned char) tolower(this->getOwner()));
            attroff(COLOR_PAIR(A_PLAYER));
            break;
        case 'B':
            attron(COLOR_PAIR(B_PLAYER));
            addch((unsigned char) tolower(this->getOwner()));
            attroff(COLOR_PAIR(A_PLAYER));
            break;
        case 'C':
            attron(COLOR_PAIR(C_PLAYER));
            addch((unsigned char) tolower(this->getOwner()));
            attroff(COLOR_PAIR(A_PLAYER));
            break;
        case 'D':
            attron(COLOR_PAIR(D_PLAYER));
            addch((unsigned char) tolower(this->getOwner()));
            attroff(COLOR_PAIR(A_PLAYER));
            break;
        default:
            break;
    }
}

unsigned long Unit::getIndex() { return index; }

void Unit::setIndex(unsigned long i) { this->index = i; }

void Unit::receiveAttack(Tile*) { --life; }

int Unit::getUCount() const { return life; }

bool Unit::isUnit() const { return true; }
