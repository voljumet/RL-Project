//
// Created by 47472 on 13.04.2022.
//
#include "battleclass.h"



using namespace std::chrono;
using namespace std;

struct axie{
    unsigned int id = 0;
    string type = "";
//    int because if health <= 0 -> dead
    int health = 0;
    unsigned int morale = 0;
    unsigned int speed = 0;
    unsigned int skill = 0;
    int playedCards[2];

    enum position {front,rear};
    card cards[4];
};

void damageMultiplyer(axie attacker){
    double multiplyer = 1;
    if(attacker.bodypart_1.type == attacker.type){
        if(attacker.bodypart_2.type == attacker.type){

        }
        multiplyer *= 0.1;
    }
}

void axieAttack(axie attacker, axie defender, int damage){

};

int reward(int r){
    return r;
}


