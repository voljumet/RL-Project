#include <iostream>
#include <vector>
#include <fstream>
#include "json/json.h"
#include "json/value.h"
using namespace std::chrono;
using namespace std;


struct card{
    string type = "";
    int damage = 0;
    int defence = 0;
    enum status {usable, unusable} status;
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
    enum position {front,rear};
    card cards[4];
};

struct player{
    unsigned int id = 0;
    axie axies [2];
    unsigned int energy = 0; // allows player to use skills
    unsigned int rank = 0; // rank of player
};



player createPlayer(int axie1, int axie2){
    player p;

    p.axies[0].type = "plant";
    p.axies->cards[0].type = "plant";
    p.axies->cards->damage = 100;
    p.axies->cards->defence = 30;

    p.axies[0].cards[0].status = card::unusable;
    p.axies[0].cards[1].status = card::unusable;
    p.axies[0].cards[2].status = card::unusable;
    p.axies[0].cards[3].status = card::unusable;



    return p;
}
/*
vector<int> sortTurnOrder(const player& player1, const player& player2){
    std::vector<int> turnOrder;

    for_each(player1.axies[0], player1.axies[2], [&turnOrder](const axie& a){
        turnOrder.push_back(a.speed);
    });

    for_each(player2.axies[0], player2.axies[2], [&turnOrder](const axie& a){
        turnOrder.push_back(a.speed);
    });

    sort(turnOrder.begin(), turnOrder.end());

    return turnOrder;
}
 */

void gameloop(){
    int axies [2];
    cin >> axies[0] >> axies[1];
    player player1 = createPlayer(111,222);
    player player2 = createPlayer(444,555);

//    check speed of axies to set turn order

   // std::vector<int> turnOrder = sortTurnOrder(player1, player2);


    int choose_card;

    cin >> choose_card;
    switch (choose_card) {
        case 1:
            cout << "You chose 1" << endl;
            break;
        case 2:
            cout << "You chose 2" << endl;
            break;
        case 3:
            cout << "You chose 3" << endl;
            break;
        default:
            cout << "You chose something else" << endl;
            break;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////


class State
{
public:
    virtual void UpdateState() = 0;
    virtual ~State(){};
};

class Card_Selection_State: public State
{
public:
    void UpdateState()  override
    {
        cout << "Cads are selected!"<< endl;
    };

    void SelectCards(player &p1, player &p2)
    {
        int input;
        cout << "Choose cards for player 1 !" << endl;
        cin >>input;
        if (input == 1) {p1.axies->cards[0].status = card::usable;}
        else if (input == 2) {p1.axies->cards[1].status = card::usable;}
        else if (input == 3) {p1.axies->cards[2].status = card::usable;}
        else if (input == 4) {p1.axies->cards[3].status = card::usable;}
        PrintPlayer(p1,p2);
    }
    void PrintPlayer(player &p1, player &p2)
    {
        cout << "Player1, card 1: "<< p1.axies->cards[0].status << endl;
        cout << "Player1: card 2: "<< p1.axies->cards[1].status<< endl;
        cout << "Player1, card 3: "<< p1.axies->cards[2].status << endl;
        cout << "Player1: card 4: "<< p1.axies->cards[3].status<< endl;
    }
    // Constructor
    Card_Selection_State(player &p1, player &p2)
    {
        cout << "Card_Selection_State is created!" << endl;
        SelectCards(p1, p2);

    }
    ~Card_Selection_State(){
        cout << "Card_Selection_State is discreated!" << endl;
    };
};

class Attack_State: public State
{
public:
    void UpdateState() override
    {
        cout << "attack done"  << endl;
    }
    void PrintPlayer(player &p1, player &p2)
    {
        cout << "Player1: "<< p1.axies->cards[0].status << endl;
        cout << "Player2: "<< p2.axies->type << endl;
    }

    // Constructor
    Attack_State(player &p1, player &p2)
    {
        cout << "Attack_State is created" << endl;
        p1.id = 30;
        p2.id = 50;
        PrintPlayer(p1,p2);
    }

    ~Attack_State(){
        cout << "Attack_State is discreated!" << endl;
    };
};

class StateController
{
private:
    State* currentState = nullptr;

public:
    void Init(player &p1, player &p2)
    {
        currentState = new Card_Selection_State(p1,p2);
    }

    void Update()
    {
        currentState->UpdateState();
    }

    void TransitionTo (char c, player &p1, player &p2)
    {
        delete currentState;
        if(c == 'a'){currentState = new Attack_State(p1, p2);}
        if(c == 'c'){currentState = new Card_Selection_State(p1, p2);}
    }

    ~StateController()
    {
        delete currentState;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    ifstream file("/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/axie_teams.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(file, obj);
    cout << "All teams: \n" << obj[0] << endl;

    int axies [2];
    player player1 = createPlayer(111,222);
    player player2 = createPlayer(444,555);

    StateController stateController;
    stateController.Init(player1, player2);
    string str = "N";
    while (str[0] != 'q')
    {
        stateController.Update();
        cin >> str;
        cout << endl;
        if (str[0] == 'a' || str[0] == 'c'){stateController.TransitionTo(str[0], player1, player2);}
    }
    //gameloop();
    return 0;
}
