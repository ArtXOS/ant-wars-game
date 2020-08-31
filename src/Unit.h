//
// Created by penguin_ib on 5/8/19.
//
#ifndef SEMESTRALKA_UNIT_H
#define SEMESTRALKA_UNIT_H

#include "Map.h"
#include "Tile.h"

/**
 * Class Unit represents the Unit of the Game. Unit inherits from Tile
 */
class Unit : public Tile {
public:
    /**
     * Constructor which creates a Unit. Initialises index to 0 and life to 1.
     * @param[in] owner - Unit owner
     * @param[in] posX - X coordinate of the Unit
     * @param[in] posY - Y coordinate of the Unit
     */
    Unit(const char owner, unsigned long posX, unsigned long posY);

    /**
     * hecks if this Tile is Spawner(Tower)
     * @return return false;
     */
    bool isSpawner() const override;

    /**
     * Prints the Unit on the map. Color and letter depend on the owner
     */
    void show() const override;

    /**
     * Getter of the index
     * @return returns index of the pos in path vector
     */
    unsigned long getIndex();

    /**
     * Changes index to i
     * @param[in] i - new index
     */
    void setIndex(unsigned long i);

    /**
     * Method to receive the attack. Unit will be lost anyway.
     * @param[in] tile - Tile which attacks us
     */
    void receiveAttack(Tile*) override;

    /**
     * Return life of the Unit
     * @return returns life
     */
    int getUCount() const override;

    /**
     * Checks if this Tile is Unit
     * @return returns true
     */
    bool isUnit() const override;

protected:
    int life;///< life of the Unit
    unsigned long index;///< current position of a Unit due to path vector
};


#endif //SEMESTRALKA_UNIT_H
