//
// Created by penguin_ib on 5/8/19.
//

#ifndef SEMESTRALKA_EMPTY_H
#define SEMESTRALKA_EMPTY_H


#include "Tile.h"

/**
 * Class represents an Empty Tile of the Map. Class inherits from the parent class Tile
 */
class Empty : public Tile {
public:
    /**
     * Default constructor. Initialises owner with '*' value
     */
    Empty();

    /**
     * Creates an instance of an Empty class
     * @param[in] owner - sets owner of the Empty tiles. Is recommended to use '*' owner for the Empty tiles
     * @param[in] posX - X coordinate in the Map
     * @param[in] posY - Y coordinate in the Map
     */
    Empty(const char owner, unsigned long posX, unsigned long posY);

    /**
     * Destructor inserts Edge *-ers from the vector "edges" into set of Edge * to free them later
     */
    ~Empty() override;

    /**
     * Checks if this Tile is a Spawner(Tower)
     * @return returns false
     */
    bool isSpawner() const override;

    /**
     * Checks if this Tile is a Wall
     * @return returns false
     */
    bool isWall() const override;

    /**
     * Checks if this Tile is a Unit
     * @return returns false
     */
    bool isUnit() const override;

    /**
     * Prints Empty tile. ' ' char is default
     */
    void show() const override;
};


#endif //SEMESTRALKA_EMPTY_H
