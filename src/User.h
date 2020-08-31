//
// Created by penguin_ib on 5/12/19.
//

#ifndef SEMESTRALKA_USER_H
#define SEMESTRALKA_USER_H


#include "Player.h"
/**
 * Class User represents real player in the Game. Mostly controls User input
 */
class User : public Player {
public:
    /**
     * Creates a User with id. By default id always will is 'A'
     * @param[in] id - player id
     */
    User(const char id);

    /**
     * Logic for creating the Move were replace to handleInput() method
     * @return returns nullptr
     */
    Move *makeMove() const override;

    /**
     * Method handles User input during the Game process. Helps to make turns, pass turns or exit tom quit menu
     * @return returns false - if there were mistakes in input, true - if everything was okay
     */
    bool handleInput() const override;
};


#endif //SEMESTRALKA_USER_H
