//
// Created by penguin_ib on 5/8/19.
//
#ifndef SEMESTRALKA_MAP_H
#define SEMESTRALKA_MAP_H

#include "Route.h"
#include "Player.h"
#include "Tower.h"
#include "Tile.h"
#include "Player.h"
#include <vector>
#include <iostream>
#include <ncurses.h>
#include <set>

class Player;
/**
 * Class represents Map of the Game. Map is made of different Tiles, with different purposes. Each Tile has its position
 */
class Map {
public:
    /**
     * Default constructor.
     */
    Map() = default;

    /**
     * Creates a Map with a dimension width x height, which will be filled with nullptrs
     * Static members width and height will be initialised with values width and height
     * @param[in] width - map width
     * @param[in] height - map height
     * @param[in] spawners - Tower pointers
     */
    Map(int width, int height, const std::vector<Tower *> &spawners);

    /**
     * Destructor inserts Route* (static member) into set of Route* to free them later
     * and inserts every Tile of Map into set of Tile* to free them later
     */
    ~Map();

    static Route *route; ///Pointer to a Route object, which finds paths for Units
    static int width; ///< Map width
    static int height; ///< Map height

    /**
     * Method gives a direct access to Tower* in the Map
     * @return returns & to a vector of Spawners(Towers*) in the Map
     */
    std::vector<Tower *> &getSpawners();

    /**
     * Method gives a direct access to every Tile* in the Map
     * @return returns & to a vector of Tile* of this Map
     */
    std::vector<std::vector<Tile *>> &getTiles();

    /**
     * Prints Map to stdscr
     */
    void printMap() const;

    /**
     * Creates an instance of Route class then assigns its pointer to a static member "route"
     */
    void createRoute() const;

    /**
     * Send copies of a vector of Spawners(Towers*) to each Player
     */
    void sendSpawnerCores();

    /**
     * Adds Spawner(Tower*) to a member vector "spawners"
     */
    void addSpawner(Tower * spawner);

    /**
     * Updates Tiles and creates new Edges after each turn
     */
    void updateNodes();

    /**
     * Method updates info about Spawners(Towers) after loading a saved game
     * @param[in] name - name of the Spawner(Tower)
     * @param[in] owner - owner of the Spawner(Tower)
     * @param[in] units - Units count in the Spawner(Tower)
     * @param[in] level - level of the Spawner(Tower)
     * @return return true if there weren't any errors, false - if were (save file could be corrupted)
     */
    bool updateSpawnerAfterLoad(const char name, const char owner, int units, int level);

    /**
     * Creates Tiles puts them into Map in according to map file. Modifies map "towerOwners" due to information from the map file
     * @param[in] filein - name of the file with a map
     * @param[in,out] towersOwners - map which contains pairs of (Tower id, Player id)
     */
    void readTilesFromFile(std::ifstream &filein, const std::map<char, char> &towersOwners);

    /**
     * Replaces Tile* on pos X,Y with new Tile* tile. Previous Tile* inserts into set of Tile* to free them later
     * @param[in] tile - Tile* to put into the map
     * @param[in] posX - X coordinate
     * @param[in] posY - Y coordinate
     */
    void replaceTile(Tile *tile, unsigned long posX, unsigned long posY);

    /**
     * Updates info about Spawner(Tower*) parts during the process of reading map from the file
     */
    void recalculateTiles();

private:
    std::vector<std::vector<Tile *> > tiles; ///<Contains pointer to each Tile* of the map
    std::vector<Tower *> spawners; ///<Contains pointer to each Spawner(Tower) of the map
};

#endif //SEMESTRALKA_MAP_H
