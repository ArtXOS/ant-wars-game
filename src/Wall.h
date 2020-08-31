//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_WALL_H
#define SEMESTRALKA_WALL_H

#include "Tile.h"

/**
 * Class Wall represents Wall part of the map, which you can reach and attack. Inherits from Tile.
 */
class Wall : public Tile {
public:

    /**
     * Constructor which creates a Wall
     * @param[in] owner - Wall owner. By default is 'N'
     * @param[in] posX -  X coordinate of the Wall
     * @param[in] posY - Y coordinate of the Wall
     */
    Wall(const char owner, unsigned long posX, unsigned long posY);

    /**
     * Destructor inserts Edge *-ers from the vector "edges" into set of Edge * to free them later
     */
    ~Wall();

    /**
     * Checks if this Tile is Spawner(Tower)
     * @return returns false;
     */
    bool isSpawner() const override;

    /**
     * Checks if this Tile is Wall. Method uses while creating nodes and edges
     * @return return true;
     */

    bool isWall() const override;
    /**
     * Prints wall
     */
    void show() const override;

};


#endif //SEMESTRALKA_WALL_H
