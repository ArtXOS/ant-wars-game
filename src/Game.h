//
// Created by penguin_ib on 5/8/19.
//

#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H

#include "Map.h"
#include "GameBin.h"
/**
 * Enumeration of Game states
 */
enum GameState {
    OtherPlayersTurns, UserTurn, Attack, Upgrade, Choosing, Choosed, Animation, Update, Winner, Exit
};

/**
 * Game class represents Game. It controls Game processes
 */
class Game {
public:
    /**
     * Default constructor
     */
    Game() = default;

    /**
     * Creates a Game with players
     * @param[in] players - players of the game
     */
    Game(std::vector<Player *> &players);

    /**
     * Destructor inserts Move* from the list of Moves into set of Move* to free them later
     */
    ~Game();

    static GameState state;///<Static member which tells us info about current Game state

    static Map *gameMap;///<Static member to access to Game map

    /**
     * Main loop of the game. Switches between different Game states
     */
    void executingLoop();

    /**
     * Tells Game map to send Spawners(Towers cores) to Game players
     */
    void giveInfoAboutSpawners() const;

    /**
     * Switches between different Game states to handle User input
     * @return returns true if an input was successful, false - if wasn't
     */
    bool userInputHandle() const;

    /**
     *
     * @return returns & to vector of Player* of this Game instance
     */
    std::vector<Player *> &getPlayers();

    /**
     * Adds Move* to a list of Moves
     * @param[in] move - Move* to add
     */
    void addMove(Move *move);

    /**
     * Method changes spawner owners
     * @param[in] previous - previous owner id
     * @param[in] next - next owner id
     * @param[in] spawner - spawner(Tower*) to change owners of
     */
    void changeSpawnerOwner(const char previous, const char next, Tile *spawner);

    /**
     * Method checks if there is a winner ( if there is only 1 Player, which owes Towers )
     * @return returns true if the winner was found, false - if other Players have enough Towers to make a turn
     */
    bool checkPlayerSpawners() const;

private:
    std::vector<Player *> players; ///<Contains pointers to Players in this Game
    std::list<Move *> moves; ///<Contains list of created Moves; Clears every turn
};

#endif //SEMESTRALKA_GAME_H