//
// Created by penguin_ib on 5/12/19.
//

#include "Bot.h"
#include "Move.h"
#include <ctime>
#include <iostream>
#include <unistd.h>

Bot::Bot(const char id) : Player(id) {}

RandomBot::RandomBot(const char id) : Bot(id) {}

PriorityBot::PriorityBot(const char id) : Bot(id) {}

Move *Bot::makeMove() const { return nullptr; }

Move *RandomBot::makeMove() const {
    Tower *start = nullptr, *target = nullptr;

    unsigned long x;
    bool move = true;

    while (true) {

        bool more = false;
        if (playerTowers.empty()) {
            move = false;
            break;
        }

        for (auto &b : playerTowers) {
            if (b->getUCount() > 22) b->upgrade();
        }

        for (auto &b : playerTowers) {
            if (b->getUCount() >= 5) more = true;
        }

        if (!more) {
            move = false;
            break;
        }

        x = (rand() % (playerTowers.size()));
        start = playerTowers.at(x);

        if (start->getUCount() > 20) start->upgrade();
        if (start->getUCount() < 5) continue;

        x = (rand() % (spawners.size()));
        target = spawners.at(x);

        if (target->getName() != start->getName()) break;
        else continue;
    }

    if (move) {
        start->minusForTurn();
        return new Move(start->getName(), target->getName(), start->getOwner());
    } else return nullptr;

}

Move *PriorityBot::makeMove() const {
    Tower *start = nullptr, *target = nullptr;

    unsigned long x;
    bool move = true;

    while (true) {

        bool more;
        bool found = false;

        if (playerTowers.empty()) {
            move = false;
            break;
        }

        for (auto &b : playerTowers) {
            if (b->getUCount() > 22) b->upgrade();
        }

        for (auto &b : playerTowers) {
            if (b->getUCount() >= 5) more = true;
        }

        if (!more) {
            move = false;
            break;
        }

        x = (rand() % (playerTowers.size()));
        start = playerTowers.at(x);

        if (start->getUCount() < 5) continue;

        for (auto &b : playerTowers) {
            if (b->getName() != start->getName() && b->getUCount() < 3) {
                target = b;
                found = true;
                break;
            }
        }

        if (found) break;

        for (auto &b : spawners) {
            if (b->getOwner() == 'N' && b->getUCount() < 5) {
                target = b;
                found = true;
                break;
            } else if (b->getOwner() != getID() && b->getOwner() != 'N' && b->getUCount() < 7) {
                target = b;
                found = true;
                break;
            }
        }

        if (found) break;

        x = (rand() % (spawners.size()));
        target = spawners.at(x);

        if (target->getName() != start->getName()) break;
        else continue;

    }

    if (move) {
        start->minusForTurn();
        return new Move(start->getName(), target->getName(), start->getOwner());
    } else return nullptr;
}


