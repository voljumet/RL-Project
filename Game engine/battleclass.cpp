//
// Created by 47472 on 13.04.2022.
//
#include "battleclass.h"
#include <iostream>
#include <chrono>
#include <vector>


using namespace std::chrono;

struct axie{
    unsigned int id = 0;
    string type = "";
//    int because if health <= 0 -> dead
    int health = 0;
    unsigned int morale = 0;
    unsigned int speed = 0;
    unsigned int skill = 0;
    int playedCards[2];
    string strenght = "";
    bool alive = true;

    enum position {front,rear};
    card cards[4];
};

void setStrenght(axie a){
    if(a.type == "Plant"){
        a.strenght = "Aqua"
    }else if(a.type == "Aqua"){
        a.strenght ="Beast"
    }else if(a.type == "Beast"){
        a.strenght == "Plant"
    }
}

void damageCalculator(axie attacker, axie defender){
    int damage = 100;

    //determines any class advantage/disadvantage based on axie type
    if(attacker.strenght == defender.type){
        damage += 15;
    }else if(defender.strenght == attacker.type){
        damage -= 15;
    }else{
        break;
    }

    //determines any card advantage based on axie type and card type
    for(int playedcards : attacker.playedCards) {
        if (attacker.cards[playedcards].type == attacker.type){
            damage += 10;
        }else{
            break;
        }
    }
    int numberofPlayed = sizeof(attacker.playedcards)/sizeof(attacker.playedcards[0])
    if(attacker.playedCards >=2){
        damage += (attacker.skill * 0.55 * numberofPlayed)
    }

}

void axieAttack(axie attacker, axie defender, int damage){
    defender.health -= damage;
    if(defender.health <= 0){
        axie.alive = false
    }
};

int reward(int r){
    return r;
}

void battle(player p1, player p2){
    //Establish the players that are battling
    //determine the order of the axies
    //input the attacking axie and the front defending axie into damage calculator
    damageCalculator(p1, p2)

    //attack the defender axie (the front axie of opposing team)
    axieAttack(a1, a2, damage)

    //repeat until one player is dead.

}

