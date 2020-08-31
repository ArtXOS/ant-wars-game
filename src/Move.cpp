//
// Created by penguin_ib on 5/12/19.
//

#include "Empty.h"
#include "Move.h"
#include "Game.h"
#include "Unit.h"
#include <unistd.h>
#include <algorithm>

Move::Move(const char from, const char to, const char player) : from(from), to(to), player(player) {
    this->state = MoveState::Created;
    this->path = Map::route->findRoute(from, to, player);
    reverse(path.begin(), path.end());
    std::vector<Unit *> tmp(5);
    for (unsigned long i = 0; i < 5; i++) { tmp.at(i) = new Unit(player, 0, 0); }
    this->units = tmp;
}

Move::~Move() { for (auto &i : path) GameBin::toDeleteTiles.insert(i); }

int Move::getState() const { return state; }

void Move::doChanges() {

    if (this->state == MoveState::Created) this->state = MoveState::First;

    switch (this->state) {
        case MoveState::First: {
            unsigned long posX1 = path.at(3)->getPosX();
            unsigned long posY1 = path.at(3)->getPosY();

            Game::gameMap->replaceTile(units.at(0), posX1, posY1);
            units.at(0)->setIndex(4);
            units.at(1)->setIndex(3);

            this->state = MoveState::Second;
            break;
        }

        case MoveState::Second: {
            for (unsigned long i = 0; i < 2; i++) {

                unsigned long posX1 = path.at(units.at(i)->getIndex())->getPosX();
                unsigned long posY1 = path.at(units.at(i)->getIndex())->getPosY();
                unsigned long posX0 = path.at(units.at(i)->getIndex() - 1)->getPosX();
                unsigned long posY0 = path.at(units.at(i)->getIndex() - 1)->getPosY();

                if (i != 1) Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                Game::gameMap->replaceTile(units.at(i), posX1, posY1);
                units.at(i)->setIndex(units.at(i)->getIndex() + 1);

            }

            units.at(2)->setIndex(3);
            this->state = MoveState::Third;

            break;
        }

        case MoveState::Third: {
            for (unsigned long i = 0; i < 3; i++) {

                unsigned long posX1 = path.at(units.at(i)->getIndex())->getPosX();
                unsigned long posY1 = path.at(units.at(i)->getIndex())->getPosY();
                unsigned long posX0 = path.at(units.at(i)->getIndex() - 1)->getPosX();
                unsigned long posY0 = path.at(units.at(i)->getIndex() - 1)->getPosY();

                if (i != 2) Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                Game::gameMap->replaceTile(units.at(i), posX1, posY1);
                units.at(i)->setIndex(units.at(i)->getIndex() + 1);

            }

            units.at(3)->setIndex(3);
            this->state = MoveState::Forth;

            break;
        }

        case MoveState::Forth: {
            for (unsigned long i = 0; i < 4; i++) {

                unsigned long posX1 = path.at(units.at(i)->getIndex())->getPosX();
                unsigned long posY1 = path.at(units.at(i)->getIndex())->getPosY();
                unsigned long posX0 = path.at(units.at(i)->getIndex() - 1)->getPosX();
                unsigned long posY0 = path.at(units.at(i)->getIndex() - 1)->getPosY();

                if (i != 3) Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                Game::gameMap->replaceTile(units.at(i), posX1, posY1);
                units.at(i)->setIndex(units.at(i)->getIndex() + 1);
            }

            units.at(4)->setIndex(3);
            this->state = MoveState::Fifth;

            break;
        }

        case MoveState::Fifth: {
            for (auto &i : units) {

                unsigned long posX1 = path.at(i->getIndex())->getPosX();
                unsigned long posY1 = path.at(i->getIndex())->getPosY();
                unsigned long posX0 = path.at(i->getIndex() - 1)->getPosX();
                unsigned long posY0 = path.at(i->getIndex() - 1)->getPosY();


                if (i->getIndex() != 3) Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                Game::gameMap->replaceTile(i, posX1, posY1);
                i->setIndex(i->getIndex() + 1);
            }

            this->state = MoveState::Usual;

            break;
        }

        case MoveState::Usual: {

            if (units.empty()) {
                this->state = MoveState::Finished;
                break;
            }

            for (unsigned long i = 0; i < units.size(); i++) {

                unsigned long posX0 = path.at(units.at(i)->getIndex() - 1)->getPosX();
                unsigned long posY0 = path.at(units.at(i)->getIndex() - 1)->getPosY();

                unsigned long posX1 = path.at(units.at(i)->getIndex())->getPosX();
                unsigned long posY1 = path.at(units.at(i)->getIndex())->getPosY();

                if (Game::gameMap->getTiles().at(posY1).at(posX1)->getOwner() != '*') {
                    Game::gameMap->getTiles().at(posY1).at(posX1)->receiveAttack(
                            Game::gameMap->getTiles().at(posY0).at(posX0));
                    Game::gameMap->getTiles().at(posY0).at(posX0)->receiveAttack(
                            Game::gameMap->getTiles().at(posY1).at(posX1));
                }

                if (Game::gameMap->getTiles().at(posY1).at(posX1)->getName() == to &&
                    Game::gameMap->getTiles().at(posY1).at(posX1)->getUCount() <= 0) {
                    char currentOwner, nextOwner;
                    currentOwner = Game::gameMap->getTiles().at(posY1).at(posX1)->getOwner();
                    nextOwner = Game::gameMap->getTiles().at(posY0).at(posX0)->getOwner();
                    Game::gameMap->getTiles().at(posY1).at(posX1)->setOwner(nextOwner);
                    GameBin::game->changeSpawnerOwner(currentOwner, nextOwner,
                                                      Game::gameMap->getTiles().at(posY1).at(posX1));
                }

                if (units.at(i)->getUCount() <= 0) {

                    Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                    GameBin::toDeleteTiles.insert(units.at(i));
                    units.erase(units.begin() + i);
                    --i;

                } else {

                    Game::gameMap->replaceTile(units.at(i), posX1, posY1);
                    Game::gameMap->replaceTile(new Empty('*', posX0, posY0), posX0, posY0);
                    units.at(i)->setIndex(units.at(i)->getIndex() + 1);
                }

            }

            break;
        }

        default:
            break;
    }
}

