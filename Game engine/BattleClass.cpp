//
// Created by 47472 on 13.04.2022.
//
#include "BattleClass.h"
#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;

void BattleClass::setStrength(Main::axie &a){
    // print out the a.type
    if(a.type == "plant"){
        a.strenght = "aqua";
    }else if(a.type == "aqua"){
        a.strenght ="beast";
    }else if(a.type == "beast"){
        a.strenght = "plant";
    }
}
// create a fucntion that sorts the axies by speed when the axie's health is not 0
std::vector<Main::axie> BattleClass::sort_axies_by_speed(player &playa){
    std::vector<Main::axie> axies_to_sort;
    for (auto &axie : playa.axies)
        if(axie.health > 0)
            axies_to_sort.push_back(axie);

    std::sort(axies_to_sort.begin(), axies_to_sort.end(), [](const Main::axie &a, const Main::axie &b) {
        return a.speed > b.speed;
    });
    return axies_to_sort;
}


void BattleClass::damageCalculator(Main::axie &attacker_axie, Main::axie &defender_axie, Main::player &p1, Main::player &p2) {
    // the damage is the attacker card base damage
    // how to know which card is attacking?
    // the attacker card is the card that is on the top of the stack?
    // could damage be the sum of both cards base damage?

    int total_damage = 0;

    for (int i = 0; i < 4; ++i) {

        //// base damage needs to reset for each card
        int base_damage = 0;
        if (attacker_axie.cards[i].card_status == Main::card::chosen_for_attack) {
            //// base damage is the card damage
            base_damage = attacker_axie.cards[i].damage;
            total_damage = base_damage;
            ////  If the Axie type is the same as the axie card type, the card will deal an extra 10% damage
            if (attacker_axie.cards[i].type == attacker_axie.type) {
                total_damage = base_damage + (base_damage * 0.1);
            }
            ////If the card class is strong against the Axie class, it will deal +15% bonus damage. Or -15% if it’s the other way.
            if (attacker_axie.strenght == defender_axie.type) {
                total_damage = base_damage + (base_damage * 0.15);
            } else if (attacker_axie.type == defender_axie.strenght) {
                total_damage = base_damage - (base_damage * 0.15);
            }

            //// set the used card to wait_for_restock
            attacker_axie.cards[i].card_status = Main::card::wait_for_restock;
        }
    }

    // print out total_damage
    if(total_damage == 0){
        total_damage = 100;
    }
    std::cout << "total_damage: " << total_damage << std::endl;

    //// reduce the health of the defender_axie by total_damage, and check if health is less than 0, then set axie.alive to false
    for (int i = 0; i < 4 ; ++i) {
        if (defender_axie.cards[i].card_status == Main::card::chosen_for_attack) {
            defender_axie.health += defender_axie.cards[i].defence;
        }
    }

    defender_axie.health -= total_damage;
        if (defender_axie.health <= 0) {
           defender_axie.alive = false;
        if (attacker_axie.health <= 0) {
            attacker_axie.alive = false;
        }
        // print out the defender_axie axie dead
        std::cout << "The defender_axie axie  is dead" << std::endl;
    }
    for (int i = 0; i < 4; ++i) {
        if (attacker_axie.id == p1.axies[i].id) {
            p1.axies[i] = attacker_axie;
        }
        if (defender_axie.id == p2.axies[i].id) {
            p2.axies[i] = defender_axie;
        }
        }

}
void BattleClass::battle(Main::player &p1, Main::player &p2){
    BattleClass battleclass;
    Main main;
    //Establish the players that are battling -- done
    //determine the order of the axies -- done

    //input the attacking axie and the front defending axie into damage calculator


    /// sort axies in the game based on speed, first axie will be the first attacker, form player1
    vector<axie> player1_axies_sorted = battleclass.sort_axies_by_speed(p1);
    vector<axie> player2_axies_sorted = battleclass.sort_axies_by_speed(p2);


    /// find the first attacking axie from player 1
    axie attacker_axie_player1 = player1_axies_sorted[0];
    /// find the first defending axie from player 2
    axie defender_axie_player2 = player2_axies_sorted[0];

    // print out the attacker and defender axies
    cout << "Player 1 attacker Axie 1 is " << attacker_axie_player1.type << endl;
    cout << "Player 2 defender Axie 1 is " << defender_axie_player2.type << endl;

    //// while at least one axie on each player is alive
    while ((p1.axies[0].alive || p1.axies[1].alive)  && (p2.axies[0].alive || p2.axies[1].alive))
    {
        /// sends attacker, defender and p1 and p2 to damage calculator, reason to send p2 is to use defence cards!
        // for each axie in player1_axies_sorted and player2_axies_sorted, send the axie to the damage calculator
        for (int i = 0; i < 2 ; ++i) {
            /// set strength of each axie before calculating damage
            battleclass.setStrength(player1_axies_sorted[i]);
            battleclass.setStrength(player2_axies_sorted[i]);
            battleclass.damageCalculator(player1_axies_sorted[i], player2_axies_sorted[i], p1, p2);
        }
        for (int i = 0; i < 2 ; ++i) {
            /// set strength of each axie before calculating damage
            battleclass.setStrength(player2_axies_sorted[i]);
            battleclass.setStrength(player1_axies_sorted[i]);
            battleclass.damageCalculator(player2_axies_sorted[i], player1_axies_sorted[i], p1, p2);
        }

       //// change state in Main to card_selection state
    }

    //battleclass.damageCalculator(attacker_axie_player1,defender_axie_player2, p1, p2);

    Main::PrintGameBoard(p1, p2,2);
    //attack the defender axie (the front axie of opposing team)
    //axieAttack(a1, a2, damage);

    //repeat until one player is dead.

}


