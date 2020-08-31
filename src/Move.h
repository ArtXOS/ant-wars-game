//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_MOVE_H
#define SEMESTRALKA_MOVE_H

#include "Player.h"
#include "Route.h"
#include "Unit.h"

class Unit;

/**
 * Enumeration of Move states
 */
enum MoveState {
    Created, Finished, First, Second, Third, Forth, Fifth, Usual
};

/**
 * Class controls Units during the Animation process, organises all logic of Units movement
 */
class Move {
public:
    /**
     * Creates an instance of the Move
     * @param from - name of the Tower, where Units will start their trip
     * @param to - name of the Tower, where Units will end their trip
     * @param player - id of the player, owner of these Units
     */
    Move(const char from, const char to, const char player);

    /**
     * Destructor inserts Tile* from vector member "path" into set of Tile* to free them later
     */
    ~Move();

    /**
     * Main loop of the trip process. Replaces Units location each iteration. Calculates Units collisions
     * and finds moments when Units start to attack other Spawners(Towers)
     */
    void doChanges();

    /**
     * Returns current Move state. Uses to find out, that every Move was finished
     * @return - returns current Move state
     */
    int getState() const;
    
private:

    MoveState state;///< Contains current Move state
    char from;///< starting Tower
    char to;///< target Tower
    char player;///< Units owner
    std::vector<Tile *> path;///< vector of Tiles* which is the path from the start to the target
    std::vector<Unit *> units;///< vector of Unit* which contains Units that are making the Move
};


#endif //SEMESTRALKA_MOVE_H
