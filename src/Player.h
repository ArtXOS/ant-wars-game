//
// Created by penguin_ib on 5/8/19.
//

#ifndef SEMESTRALKA_PLAYER_H
#define SEMESTRALKA_PLAYER_H

#include "Tile.h"
#include "Tower.h"
#include "Move.h"
#include "Map.h"
#include <map>
#include <vector>

#define LEVEL 1 //You can change hardness level - 0 or 1

class Map;

class Move;

/**
 * Enumeration of Players' ids
 *
 */
enum PlayerID {
    A, B, C, D
};

/**
 * Class Player is an abstract class which represents a players, who take part in the Game
 */
class Player {
public:
    /**
     * Constructor is used by child classes
     * @param[in] id - player id
     */
    Player(const char id);

    /**
     * Default destructor
     */
    virtual ~Player() = default;

    /**
     * Abstract method a class. Should be implemented by its children
     * @return should return a Move*
     */
    virtual Move *makeMove() const = 0;

    /**
     * Method to receive Player id
     * @return return player id as char
     */
    char getID() const;

    /**
     * Uses to find out, how many Spawners(Towers) owes Player
     * @return returns size of the member vector "playerTowers"
     */
    unsigned long getTowersCount() const;

    /**
     * Uses to find out, that Player doesn't owe any Spawner(Tower)
     * @return returns true, if vector "playerTowers" is empty, false - if isn't
     */
    bool isTowersEmpty() const;

    /**
     * Uses during the Game initialisation, to give Players info about Spawners(Towers) in the map
     * @param[in] spawners - & to a vector of spawners, which will be received
     */
    void recieveSpawners(std::vector<Tower *> &spawners);

    /**
     * Adds Spawner(Tower*) to vector "playerTowers"
     * @param[in] spawner - pointer to the spawner, which will be added
     */
    void addSpawner(Tile *spawner);

    /**
     * Removes Spawner(Tower*) from vector "playerTowers"
     * @param[in] spawner - pointer to the spawner, which will be removed
     */
    void removeSpawner(Tile *spawner);

    /**
     * Erase the content of the vector "playerTowers"
     */
    void erasePlayerTowers();

    /**
     * Method uses to handle Player input during the Game process. Mostly in the bottom Menu under then Map
     * @return - returns true, if everything was okay, false - if there were mistakes in the input
     */
    virtual bool handleInput() const;

protected:
    std::vector<Tower *> spawners;///<Contains pointers to all Spawners(Towers*) in the map
    std::vector<Tower *> playerTowers; ///<Contains pointers to Player Spawners(Towers*)
    PlayerID id;///< user id (A,B,C,D)

private:

    std::map<char, PlayerID> toEnum{{'A', A},
                                    {'B', B},
                                    {'C', C},
                                    {'D', D}};///<helps interpret char to enum
    std::map<PlayerID, char> toChar{{A, 'A'},
                                    {B, 'B'},
                                    {C, 'C'},
                                    {D, 'D'}};///<helps interpret enum to char

};


#endif //SEMESTRALKA_PLAYER_H
