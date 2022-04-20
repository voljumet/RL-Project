//
// Created by 47472 on 13.04.2022.
//
#include "BattleClass.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <map>

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


void BattleClass::damageCalculator(Main::axie &attacker_axie, Main::axie defender_axie, Main::player &p1, Main::player &p2,int num) {
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

        // print out the defender_axie axie dead
        std::cout << "The defender_axie axie  is dead" << std::endl;
    }
    for (int i = 0; i < 2; ++i) {
        if (num == 1) {
            if (attacker_axie.id == p1.axies[i].id) {
                p1.axies[i] = attacker_axie;
            }
            if (defender_axie.id == p2.axies[i].id) {
                p2.axies[i] = defender_axie;
            }
        }
        if (num == 2) {
            if (attacker_axie.id == p2.axies[i].id) {
                p2.axies[i] = attacker_axie;
            }
            if (defender_axie.id == p1.axies[i].id) {
                p1.axies[i] = defender_axie;
            }
        }
    }

}


Main::axie Find_defender_axie(Main::player p){
    //// find the defending axie taking the position in account.  /// done
    for (auto & i : p.axies) {
        int front = 0;
        int back = 0;
        for (auto & i : p.axies){
            if(i.position == Main::axie::position::front && i.alive){
                front += 1;
            }
            if(i.position == Main::axie::position::back && i.alive){
                back += 1;
            }

        }
        // if front is 2, then chose an axie randomly
        if (front == 2) {
            srand(time(0));
            int random_num = rand() % 2;
            if (random_num == 0) {
                return p.axies[0];
            }
            else {
                return p.axies[1];
            }
        }

        // if back is 2, then chose an axie randomly
        if (back == 2) {
            srand(time(0));
            int random_num = rand() % 2;
            if (random_num == 0) {
                return p.axies[0];
            }
            else {
                return p.axies[1];
            }
        }
        if (i.alive && front != 2) {
            if(i.position == Main::axie::position::front){
                return  i;
            }else if (i.position == Main::axie::position::back){
                return  i;
            }
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

    vector<axie> sorted_axies = main.sort_axies(p1, p2);

    // for each axie in the sorted axxie, check if any axie has a card that is chosen_for_attack, if not pop from the sorted_axie vector
    for (int i = 0; i < sorted_axies.size(); i++) {
        int num = 0;
        for (auto & card : sorted_axies[i].cards) {
            if(!card.chosen_for_attack){
               num += 1;
                // check if num is 4 then erase the axie from the sorted_axie vector
                if (num == 4) {
                    sorted_axies.erase(sorted_axies.begin() + i);
                }
            }
        }
    }

    // create a mapping with axie as key and player as value
    std::map<int, Main::player> axie_player_map;

    for (int i = 0; i < sorted_axies.size(); i++) {
        for (int j = 0; j < 2; j++){
            if (sorted_axies[i].id == p1.axies[j].id) {
                axie_player_map.insert(pair<int, Main::player>(sorted_axies[i].id, p1));
            }
            if (sorted_axies[i].id == p2.axies[j].id) {
                axie_player_map.insert(pair<int, Main::player>(sorted_axies[i].id, p2));
            }
        }
    }


    //// while at least one axie on each player is alive


    for (int i = 0; i < sorted_axies.size() ; i++){
        if ((p1.axies[0].alive || p1.axies[1].alive)  && (p2.axies[0].alive || p2.axies[1].alive)) {
            setStrength(sorted_axies[i]);

            // if axie_player_map[sorted_axies[i]] value is player one, then player one attacks

            Main::axie defender_axie;
            int attackNum;
            cout << axie_player_map[sorted_axies[i].id].id << endl;
            if (axie_player_map[sorted_axies[i].id].id == p1.id){
                defender_axie = Find_defender_axie(p2);
                attackNum = 1;
            } else {
                defender_axie = Find_defender_axie(p1);
                attackNum = 2;
            }

            battleclass.damageCalculator(sorted_axies[i], defender_axie, p1, p2, attackNum);
        }
    }

    //battleclass.damageCalculator(attacker_axie_player1,defender_axie_player2, p1, p2);

    Main::PrintGameBoard(p1, p2,2);
    //attack the defender axie (the front axie of opposing team)
    //axieAttack(a1, a2, damage);

    //repeat until one player is dead.

}


