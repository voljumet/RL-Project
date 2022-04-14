//
// Created by 47472 on 13.04.2022.
//

#ifndef RL_PROJECT_BATTLECLASS_H
#define RL_PROJECT_BATTLECLASS_H
#include "Main.h"


class BattleClass : public Main {
public:
    void damageCalculator(Main::axie &attacker, Main::axie &defender, Main::player &player1, Main::player &player2);
    void axieattack();
    void setStrenght();
    void battle(player &player1, player &player2);
    int reward();

};


#endif //RL_PROJECT_BATTLECLASS_H
