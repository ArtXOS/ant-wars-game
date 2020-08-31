//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_TOWER_H
#define SEMESTRALKA_TOWER_H

#include <map>
#include "Tile.h"

/**
 * Enumeration of Spawner(Tower) parts
 */
enum TowerPart {
    Core, Walls, LeftLevel, RightLevel, ULetter, SLetter, UCenter, URight, SCenter, SRight
};

/**
 * Tower represents an Spawner Tile of the Map. Class inherits from the parent class Tile
 * Players owe Towers. It's also a place, where Units produce itself
 */
class Tower : public Tile {
public:

    /**
     * Creates an instance of the Tower. By default the part is "Walls"
     * @param owner - owner of the Tower
     * @param posX - coordinate X
     * @param posY - coordinate Y
     * @param name - name of the Tower
     * @param core - central Tile* of the Tower
     */
    Tower(const char owner, unsigned long posX, unsigned long posY, const char name = '-', Tile *core = nullptr);

    /**
     * Destructor inserts Edge *-ers from the vector "edges" into set of Edge * to free them later
     */
    ~Tower();

    /**
     * Tells if this Tile is Spawner
     * @return returns true, if the part is Core, else returns false
     */
    bool isSpawner() const override;

    /**
     * Tells if this Tile is Wall
     * @return returns false;
     */
    bool isWall() const override;

    /**
     * Setter of the Tower part
     * @param[in] tmp - part id
     */
    void setPart(char tmp) override;

    /**
     * Setter of the Tower owner
     * @param[in] newOwner - new Tower owner
     */
    void setOwner(const char newOwner) override;

    /**
     * Sets the central part of the Tower
     * @param[in] core - Tile * core
     */
    void setCore(Tile *core);

    /**
     * Setter of the Units count inside the Tower
     * @param[in] count - new Unit count
     */
    void setUCount(int count) override;

    /**
     * Setter of the Tower level
     * @param[in] level - new level
     */
    void setLevel(int level) override;

    /**
     * Prints the Tower due to it part
     */
    void show() const override;

    /**
     * Getter of the Tower name
     * @return returns Tower name
     */
    char getName() const override;

    /**
     * Getter of the central Tile of the Tower
     * @return returns Tile* of the CorePart
     */
    Tile *getCore() const override;

    /**
     * Getter of the Unit count
     * @return returns count of Units in the Tower
     */
    int getUCount() const override;

    /**
     * Getter of the Tower level
     * @return returns level
     */
    int getLevel();

    /**
     * Updates the information about the Tower when starting Game from save
     * @param[in] owner - owner id
     * @param[in] units - number of Units
     * @param[in] level - level of the Tower
     */
    void updateAfterSave(const char owner, int units, int level);

    /**
     * Changes the owner of the whole Tower
     * @param[in] owner - new owner of the tower
     */
    void updateOwner(const char owner) override;

    /**
     * Increases Unit count each turn. Depends on the level of the Tower, and the fact if the was taken by someone
     * @param[in] loser
     */
    void updateUnitCount(bool loser);

    /**
     * Add level to a Tower. Calls addLevel() and minusForUpgraded() for an each part
     */
    void upgrade();

    /**
     * Decreases Unit count by 20 to make add level
     */
    void minusForUpgrade() override;

    /**
     * Decreases Unit count by 5 to make a Move
     */
    void minusForTurn();

    /**
     * Receive Attack from another Tile. If Tower owner and another Tile owner are same - calls plusForAttack();
     * If Tower owner and another Tile owner are different - calls minusForAttack();
     * @param[in] tile - Tile, which attacks us
     */
    void receiveAttack(Tile *tile) override;

    /**
     * Decrements Units count by 1
     */
    void minusForAttack() override;

    /**
     * Increments Units count by 1
     */
    void plusForAttack() override;

    /**
     * If the level is lower/equal to 2 - increments it by 1
     */
    void addLevel() override;

private:

    /**
     * Decreases Units count by 5
     */
    void minusUnits() override;

    TowerPart part;///< tells which part this Tile is
    std::map<char, TowerPart> charToPart{{'c', Core},
                                         {'w', Walls},
                                         {'e', RightLevel},
                                         {'q', LeftLevel},
                                         {'u', ULetter},
                                         {'s', SLetter},
                                         {'z', UCenter},
                                         {'x', URight},
                                         {'v', SCenter},
                                         {'b', SRight}};///< interprets chars to enum TowerPart
    Tile *core;///< Cental part of the Tower
    int units;///< Units count
    int level;///< Tower level
    char name;///< name of the Tower

};


#endif //SEMESTRALKA_TOWER_H
