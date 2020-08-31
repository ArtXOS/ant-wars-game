//
// Created by penguin_ib on 5/8/19.
//
#ifndef SEMESTRALKA_TILE_H
#define SEMESTRALKA_TILE_H

#include <list>

#define A_PLAYER 1
#define B_PLAYER 2
#define C_PLAYER 3
#define D_PLAYER 4
#define N_PLAYER 5
#define A_PLAYER_WALL 6
#define B_PLAYER_WALL 7
#define C_PLAYER_WALL 8
#define D_PLAYER_WALL 9
#define N_PLAYER_WALL 10
#define WALL_COLOR 11
#define CORE_COLOR 12
#define EMPTY ' '
#define WALL '#'

/**
 * Function to initialise colors
 */
void initColors();

class Edge;

/**
 * Class Tile represents the base part of map. Tile can be of different types,
 * which is represented by classes, which inherits from Tile
 */
class Tile {
public:

    /**
     * Default constructor
     */
    Tile() = default;

    /**
     * Creates a Tile with an owner, on a position X,Y of the map
     * @param owner - id of the owner
     * @param posX - X coordinate of a Tile
     * @param posY - Y coordinate of a Tile
     */
    Tile(const char owner, unsigned long posX, unsigned long posY);

    /**
     * Destructor inserts Edge *-ers from the vector "edges" into set of Edge * to free them later
     */
    virtual ~Tile();

    /**
     * Getter of a X coordinate
     * @return returns X coordinate of a Tile
     */
    unsigned long getPosX() const;

    /**
     *  Getter of a Y coordinate
     * @return returns Y coordinate of a Tile
     */
    unsigned long getPosY() const;

    /**
     * Getter of the Tile owner
     * @return return owner's id
     */
    char getOwner() const;

    /**
     * Method has to be overrode in classes, which inherit from Tile
     * @return returns nullptr
     */
    virtual Tile *getCore() const;

    /**
     * Getter of the Tile name. Method has to be overrode in classes, which inherit from Tile
     * @return returns name of the tile
     */
    virtual char getName() const;

    /**
     * Getter of the Unit count. Method has to be overrode in classes, which inherit from Tile
     * @return returns 0;
     */
    virtual int getUCount() const;

    /**
     * Tells if the Tile is Spawner. Method has to be overrode in classes, which inherit from Tile
     * @return return false;
     */
    virtual bool isSpawner() const;

    /**
     * Tells if the Tile is Wall.Method has to be overrode in classes, which inherit from Tile
     * @return return false;
     */
    virtual bool isWall() const;

    /**
     * Sets the owner of the Tile
     * @param[in] newOwner - id of the new owner of the Tile
     */
    virtual void setOwner(const char newOwner);

    /**
     * Sets the part of the Tile. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void setPart(const char);

    /**
     * Sets the level of the Tile. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void setLevel(int);

    /**
     * Sets the Unit count of the Tile. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void setUCount(int);

    /**
     * Sets the owner count of the Tile. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void updateOwner(const char);

    /**
     * Adds Edge* to the vector "edges" by conecting THIS Tile with another Tile
     * @param tile - Tile* to connect with
     */
    virtual void addEdge(Tile * tile);

    /**
     * Clears vector "edge" and inserts Edge *-ers from the vector "edges" into set of Edge * to free them later
     */
    void deleteEdges();

    /**
     * Adds level to the Tile. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void addLevel();

    /**
     * Method has to be overrode in classes, which inherit from Tile
     */
    virtual void plusForAttack();

    /**
     *Shows the Tile*. Method has to be overrode in classes, which inherit from Tile
     */
    virtual void show() const;

    /**
     * Receive an attack from another Tile* Method has to be overrode in classes, which inherit from Tile
     */
    virtual void receiveAttack(Tile *);

    /**
     * Method has to be overrode in classes, which inherit from Tile
     */
    virtual void minusUnits();

    /**
     * Method has to be overrode in classes, which inherit from Tile
     */
    virtual void minusForAttack();

    /**
     * Method has to be overrode in classes, which inherit from Tile
     */
    virtual void minusForUpgrade();

    /**
     * Tells if this Tile is Unit. Method has to be overrode in classes, which inherit from Tile
     * @return returns false
     */
    virtual bool isUnit() const;

    std::list<Edge *> edges;///< contains Edge pointers of an each Tile

protected:

    char owner;///< owner the Tile
    unsigned long posX;///< X coordinate of the Tile
    unsigned long posY;///< Y coordinate of the Tile

};

/**
 * Class represents connection between two Tiles
 */
class Edge {
public:
    /**
     * Creates an Edge between two Tiles a & b
     * @param[in] from - Tile * from
     * @param[in] to - Tile * to
     */
    Edge(Tile * from, Tile * to);

    /**
     * Default destructor
     */
    ~Edge() = default;

    /**
     * Return Tile pointer which you can reach in this Edge
     * @return returns Tile pointer
     */
    Tile *getTo();

private:

    Tile *from;///< Tile * from - start
    Tile *to;///< Tile * to - target
};


#endif //SEMESTRALKA_TILE_H
