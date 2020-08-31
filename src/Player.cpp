//
// Created by penguin_ib on 5/8/19.
//

#include "Player.h"
#include "Menu.h"
#include <iostream>

Player::Player(const char tmp) { id = toEnum.find(tmp)->second; }

bool Player::handleInput() const { return false; }

char Player::getID() const { return toChar.find(id)->second; }

void Player::recieveSpawners(std::vector<Tower *> &spawners) {
    this->spawners = spawners;
    if (Menu::newGame) {
        for (auto &i : this->spawners) {
            if (i->getOwner() == this->getID()) { playerTowers.emplace_back(i); }
        }
    }
}


void Player::addSpawner(Tile *spawner) { playerTowers.emplace_back((Tower *) spawner); }

void Player::removeSpawner(Tile *spawner) {
    for (unsigned long i = 0; i < playerTowers.size(); i++) {
        if (playerTowers.at(i)->getName() == spawner->getName()) playerTowers.erase(playerTowers.begin() + i);
        else continue;
    }
}

bool Player::isTowersEmpty() const { return playerTowers.empty(); }

void Player::erasePlayerTowers() { playerTowers.clear(); }

unsigned long Player::getTowersCount() const { return playerTowers.size(); }
