//
// Created by 47472 on 13.04.2022.
//
#include "BattleClass.h"
#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;


void setStrength(Main::axie a){
    if(a.type == "Plant"){
        a.strenght = "Aqua";
    }else if(a.type == "Aqua"){
        a.strenght ="Beast";
    }else if(a.type == "Beast"){
        a.strenght == "Plant";
    };
}

void BattleClass::damageCalculator(Main::axie &attacker, Main::axie &defender, Main::player &p1, Main::player &p2){
    int damage = 100;

    vector<Main::card> chosenCards;
    /// som code can be used here ------------------- chosen cards can be found inside player struct ----------
    for (int i = 0; i < 4; ++i) {
        if(p1.axies[0].cards[i].card_status == Main::card::chosen_for_attack){
            cout << "Player " << p1.id << " Axie 1 card " << p1.axies[0].cards[i].id << " is " << p1.axies[0].cards[i].type<<" Chosen" << endl;
        }
        if(p1.axies[1].cards[i].card_status == Main::card::chosen_for_attack){
            cout << "Player " << p1.id << " Axie 2 card " << p1.axies[1].cards[i].id << " is " << p1.axies[1].cards[i].type<<" Chosen" << endl;
        }
    }
//    p1.axies[0].cards[0].card_status;
    /// ---------------------------------------------------------------------------------------------------------

    //determines any class advantage/disadvantage based on axie type
    if(attacker.strenght == defender.type){
        damage += 15;
    }else if(defender.strenght == attacker.type){
        damage -= 15;
    }else{
//        break;
    }

//    vector<Main::card> card = playedCards;

    //determines any card advantage based on axie type and card type
//    for(int playedcards : attacker.playedCards) {
//        if (attacker.cards[playedcards].type == attacker.type){
//            damage += 10;
//        }else{
//            break;
//        }
//    }
//    //must be rewritten to fit new card struct and axie struct
//    int numberofPlayed = sizeof(attacker.playedcards)/sizeof(attacker.playedcards[0]);
//    if(attacker.playedCards >=2){
//        damage += (attacker.skill * 0.55 * numberofPlayed)
//    };

}


void axieAttack(Main::axie &attacker, Main::axie &defender, int damage){
    defender.health -= damage;
    if(defender.health <= 0){
        defender.alive = false;
    }
};

int reward(int r){
    return r;
}

void BattleClass::battle(Main::player &p1, Main::player &p2){
    BattleClass battleclass;
    Main main;
    //Establish the players that are battling -- done
    //determine the order of the axies -- done

    //input the attacking axie and the front defending axie into damage calculator


    /// sort axies in the game based on speed, first axie will be the first attacker
    vector<axie> axies_sorted = main.sort_axies(p1, p2);

    /// find the first defending axie
    axie axie_defender = axies_sorted[0];

    /// sends attacker, defender and p1 and p2 to damage calculator, reason to send p2 is to use defence cards!
    battleclass.damageCalculator(axies_sorted[0], axie_defender, p1, p2);

    //attack the defender axie (the front axie of opposing team)
    //axieAttack(a1, a2, damage);

    //repeat until one player is dead.

}


