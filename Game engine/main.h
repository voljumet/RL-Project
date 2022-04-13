//
// Created by alex on 13/04/2022.
//

#ifndef GAME_ENGINE_MAIN_H
#define GAME_ENGINE_MAIN_H
#include <iostream>
#include <vector>
using namespace std;

class State
{
public:
    virtual void UpdateState() = 0;
    virtual ~State(){};
};

class main {


public:
    struct card{
        int id ;
        string type = "";
        int damage = 0;
        int defence = 0;
        enum status {usable, unusable, used} status;
    };

    struct axie{
        unsigned int id = 0;
        string type = "";
    //    int because if health <= 0 -> dead
        int health = 0;
        unsigned int morale = 0;
        unsigned int speed = 0;
        unsigned int skill = 0;
        int bodypart_1 [2] = {0,0};
        int bodypart_2 [2] = {0,0};
        enum position {front,rear}
        position = front;
        card cards[4];
    };

    struct player{
        unsigned int id = 0;
        axie axies [2];
        unsigned int energy = 0; // allows player to use skills
        unsigned int rank = 0; // rank of player
    };



};

#endif //GAME_ENGINE_MAIN_H
