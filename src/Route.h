//
// Created by penguin_ib on 5/18/19.
//

#ifndef SEMESTRALKA_ROUTE_H
#define SEMESTRALKA_ROUTE_H

#include "Tile.h"
#include "Tower.h"
#include <vector>
#include <unordered_map>

/**
 * Class Route helps to find a path for Units from
 * the start to target by using A* algorithm with
 * the same cost for an each Edge
 */
class Route {
public:
    /**
     * Creates an instance of a Route
     * @param[in] tiles - vector & of the map tiles
     * @param[in] spawners - vector & of the spawners(towers) in the map
     */
    Route(const std::vector<std::vector<Tile *> > &tiles, const std::vector<Tower *> &spawners);

    /**
     * Default destructor
     */
    ~Route() = default;

    /**
     * Method finds a path from start to target
     * @param[in] fromT - char, name of start Spawner(Tower)
     * @param[in] toT - char, name of a target Spawner(Tower)
     * @param[in] player - player, who asks to find a path
     * @return returns vector with Tile* that makes the path from start to target
     */
    std::vector<Tile *> findRoute(const char fromT, const char toT, const char) const;

private:


    struct PriorityQueue;///<struct which orders Tiles by the priority. Tiles which are closer to target have higher priority

    /**
     * Helps define how far two Tiles are from each other
     * @param[in] a - Tile * a
     * @param[in] b - Tile * b
     * @return returns abs of sum of the differences between X and Y coordinates of each tower
     */
    double heuristic(Tile *a, Tile *b) const;

    /**
     * Cost of the Move. Graph has unified cost
     * @return always return 1
     */
    double cost(Tile *, Tile *) const;

    /**
     * Method reconstructs the path with a help of a map, which remembers all
     * previous positions and returns reconstructed path from start to target
     * @param[in] start - Tile * start
     * @param[in] goal  - Tile * target/goal
     * @param[in] came_from - unordered map of the connected Tiles with each other
     * @return returns reconstructed path, which was previously created by "findRoute" method
     */
    std::vector<Tile *> reconstruct_path(Tile *start, Tile *goal, std::unordered_map<Tile *, Tile *> &came_from) const;

    std::vector<std::vector<Tile *> > tiles; ///< containes pointers to all Tiles of the map
    std::vector<Tower *> spawners; ///< contains pointers to all Spawners(Towers) in the map
};

#endif //SEMESTRALKA_ROUTE_H
