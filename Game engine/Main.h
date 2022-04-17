//
// Created by alex on 13/04/2022.
//

#ifndef GAME_ENGINE_MAIN_H
#define GAME_ENGINE_MAIN_H
#include <iostream>
#include <vector>
using namespace std;

class State {
public:
    virtual void UpdateState() = 0;
    virtual ~State(){};

};

class Main {
public:
    struct card{
        int id = 999;
        string name = "";
        string type = "";
        int damage = 0;
        int defence = 0;

        //// can_be_chosen = can be chosen by player for attack
        //// chosen_for_attack = are chosen for attack
        //// wait_for_restock = are used and must wait to be restocked before being used again
        enum status {can_be_chosen, chosen_for_attack, wait_for_restock} card_status = can_be_chosen;
    };

    struct axie{
        unsigned int id = 0;
        string type = "";
        int health = 0;
        bool alive = true;
        unsigned int morale = 0;
        unsigned int speed = 0;
        unsigned int skill = 0;
        enum position {front,back} position = front;
        string strenght = "";
        card cards[4];
    };

    struct player{
        unsigned int id = 0;
        axie axies [2];
        unsigned int energy = 0; // allows player use cards in battle
        unsigned int rank = 0; // player rank
    };

    std::vector<Main::axie> sort_axies(player &playa1, player &playa2);
    string axiePosition(axie &axie, bool is_first, string stats);
    string printAxies(player &playa1, player &playa2, vector<axie> axies);
    void PrintGameBoard(player &player1, player &player2, int round);
};

#endif //GAME_ENGINE_MAIN_H
