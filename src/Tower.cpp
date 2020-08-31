//
// Created by penguin_ib on 5/12/19.
//

#include "Tower.h"
#include "Game.h"
#include <map>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string>
#include <ostream>
#include <curses.h>

Tower::Tower(const char owner, unsigned long posX, unsigned long posY, const char name, Tile *core) : Tile(owner, posX,
                                                                                                           posY) {
    this->part = Walls;
    this->core = core;
    this->name = name;
    this->units = 15;
    this->level = 0;
}

Tower::~Tower() { if (!edges.empty()) for (auto &i : edges) GameBin::toDeleteEdges.insert(i); }

bool Tower::isSpawner() const { if (!part) return true; else return false; }

bool Tower::isWall() const { return false; }

void Tower::setPart(char tmp) { this->part = charToPart.find(tmp)->second; }

char Tower::getName() const { return name; }

Tile *Tower::getCore() const { return core; }

int Tower::getUCount() const { return units; }

void Tower::setCore(Tile *core) { this->core = core; }

int Tower::getLevel() { return level; }

void Tower::setLevel(int level) { this->level = level; }

void Tower::setUCount(int count) { this->units = count; }

void Tower::addLevel() { if (level < 3) ++level; }

void Tower::minusForUpgrade() { if (level < 3) units -= 20; }

void Tower::minusUnits() { this->units = this->units - 5; }

void Tower::minusForAttack() { --units; }

void Tower::plusForAttack() { ++units; }

void Tower::updateOwner(char owner) { this->owner = owner; }

void Tower::show() const {
    switch (this->part) {
        case Core:
            attron(COLOR_PAIR(CORE_COLOR));
            addch((unsigned char) this->getName());
            attroff(COLOR_PAIR(CORE_COLOR));
            break;
        case Walls:
            switch (owner) {
                case 'A':
                    attron(COLOR_PAIR(A_PLAYER_WALL));
                    addch((unsigned char) this->getOwner());
                    attroff(COLOR_PAIR(A_PLAYER_WALL));
                    break;
                case 'B':
                    attron(COLOR_PAIR(B_PLAYER_WALL));
                    addch((unsigned char) this->getOwner());
                    attroff(COLOR_PAIR(B_PLAYER_WALL));
                    break;
                case 'C':
                    attron(COLOR_PAIR(C_PLAYER_WALL));
                    addch((unsigned char) this->getOwner());
                    attroff(COLOR_PAIR(C_PLAYER_WALL));
                    break;
                case 'D':
                    attron(COLOR_PAIR(D_PLAYER_WALL));
                    addch((unsigned char) this->getOwner());
                    attroff(COLOR_PAIR(D_PLAYER_WALL));
                    break;
                case 'N':
                    attron(COLOR_PAIR(N_PLAYER_WALL));
                    addch((unsigned char) this->getOwner());
                    attroff(COLOR_PAIR(N_PLAYER_WALL));
                    break;
                default:
                    break;
            }
            break;
        case RightLevel:
            if (level >= 1) {
                attron(COLOR_PAIR(N_PLAYER));
                addch('*');
                attroff(COLOR_PAIR(N_PLAYER));
            } else
                addch(' ');
            break;
        case LeftLevel:
            if (level == 2) {
                attron(COLOR_PAIR(N_PLAYER));
                addch('*');
                attroff(COLOR_PAIR(N_PLAYER));
            } else
                addch(' ');
            break;
        case SLetter:
            addch(' ');
            break;
        case ULetter:
            addch('u');
            break;
        case SRight:
            addch(' ');
            break;
        case SCenter:
            addch(' ');
            break;
        case UCenter:
            if (units >= 100) addch('~');
            else printw("%d", units / 10 % 10);
            break;
        case URight:
            if (units >= 100) printw("%d", units / 10 % 10);
            else printw("%d", units % 10);
            break;
    }
}

void Tower::upgrade() {
    for (auto x = -2; x <= 2; x++) {
        for (auto y = -2; y <= 2; y++) {
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->addLevel();
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->minusForUpgrade();
        }
    }
}

void Tower::minusForTurn() {
    for (auto x = -2; x <= 2; x++) {
        for (auto y = -2; y <= 2; y++) {
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->minusUnits();
        }
    }
}

void Tower::updateUnitCount(bool loser) {
    switch (level) {
        case 0:
            if (!loser && owner != 'N')units += 5;
            else if (owner != 'N') units = 1;
            break;
        case 1:
            if (!loser && owner != 'N') units += 8;
            else if (owner != 'N')units = 2;
            break;
        case 2:
            if (!loser && owner != 'N') units += 12;
            else if (owner != 'N')units = 3;
            break;
        default:
            break;
    }
}

void Tower::receiveAttack(Tile *tile) {
    for (auto x = -2; x <= 2; x++) {
        for (auto y = -2; y <= 2; y++) {
            if (tile->getOwner() != owner)
                Game::gameMap->getTiles().at(this->getCore()->getPosY() + y).at(core->getPosX() + x)->minusForAttack();
            else if (tile->getOwner() == owner)
                Game::gameMap->getTiles().at(this->getCore()->getPosY() + y).at(core->getPosX() + x)->plusForAttack();
        }
    }
}

void Tower::setOwner(char newOwner) {
    for (auto x = -2; x <= 2; x++) {
        for (auto y = -2; y <= 2; y++) {
            ((Tower *) (Game::gameMap->getTiles().at(core->getPosY() + y).at(core->getPosX() + x)))->updateUnitCount(
                    true);
            ((Tower *) (Game::gameMap->getTiles().at(core->getPosY() + y).at(core->getPosX() + x)))->updateOwner(
                    newOwner);
        }
    }
}

void Tower::updateAfterSave(char owner, int units, int level) {
    for (auto x = -2; x <= 2; x++) {
        for (auto y = -2; y <= 2; y++) {
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->setUCount(units);
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->setLevel(level);
            Game::gameMap->getTiles().at(this->getPosY() + y).at(this->getPosX() + x)->updateOwner(owner);
        }
    }
}
