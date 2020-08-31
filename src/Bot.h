//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_BOT_H
#define SEMESTRALKA_BOT_H

#include "Player.h"

/**
 * This class is intented to represent computer in the game.
 * AI has 2 levels: RandomBot and PriorityBot
 */
class Bot : public Player {
public:
    /**
     * Constructor creates new instance of a Bot class.
     * Bot will have id(name) - 'id'
     * @param[in] id of player (A,B,C,D);
     */
    Bot(const char id);
    /**
     * This method was inherited from the parent class Player.
     * Method is overloaded to work properly in child classes
     * @return always returns nullptr
     */
    virtual Move *makeMove() const override;

};

/**
 * RandomBot has the lowest AI level. Inherits from Bot class
 */
class RandomBot : public Bot {
public:
    /**
     * Constructor creates new instance of a RandomBot class.
     * RandomBot will have id(name) - 'id'
     * @param[in] id of player (A,B,C,D);
     */
    RandomBot(const char id);

    /**
     * Method randomly finds start Tower and target Tower
     * Controls if Bot has a Tower with a count of units more than 5
     * If there are Tower in a vector "playerTowers", which can be upgraded (has more than 20 Units), method will upgrade it
     * @return returns Move *, in case of impossibility to make Move - returns nullptr
     */
    Move *makeMove() const override;

};

/**
 * PriorityBot has better AI level then RandomBot. Inherits from Bot class
 */
class PriorityBot : public Bot {
public:
    /**
     * Constructor creates new instance of a PriorityBot class.
     * PriorityBot will have id(name) - 'id'
     * @param[in] id of player (A,B,C,D);
     */
    PriorityBot(const char id);

    /**
     * Method randomly finds a Tower, which can be upgraded (has more than 20 Units), then randomly chooses start Tower
     * Priorities in finding target Tower:
     * 1. Towers of this Bot, which have less than 3 Units
     * 2. Neutral Towers, which have less than 5 Units
     * 3. Enemy Towers, which have less than 7 Units
     * 4. Random Tower
     * @return returns Move *, in case of impossibility to make Move - returns nullptr
     */
    Move *makeMove() const override;
};


#endif //SEMESTRALKA_BOT_H
