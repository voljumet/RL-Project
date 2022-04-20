#include <iostream>
#include <vector>
#include <fstream>
#include <json/json.h>
//#include "Main.h"
#include "BattleClass.h"



//// RNG
vector<int> Main::selectFourNumbers(){
    // function that select four random numbers between 0 and 7, and a number can not be repeated
    // if the number is repeated, it will be replaced by another number
    // the number of numbers will be 4 and the range is 0 to 7
    // the function will return a vector of 4 numbers
    srand(time(0));
    vector<int> random_number;
    int number;
    int i = 0;
    while(i < 4){
        number = rand() % 8;
        if(find(random_number.begin(), random_number.end(), number) == random_number.end()){
            random_number.push_back(number);
            i++;
        }
    }
    return random_number;
}

//// returns cards that CAN be chosen by player
vector<int> Main::showCardsDrawn(Main::player &p) {
    vector<int> cards_drawn = selectFourNumbers();
    // check if the number is between 0 and 3, if so find the card that have the same card id
    Main::axie &_axie1 = p.axies[0];
    Main::axie &_axie2 = p.axies[1];
    cout << "player-id " << p.id << " is choosing cards:" << endl;
    for (int i = 0; i < 4; ++i) {
        int uc_num = cards_drawn[i];
        
/// NEEDS MORE CODE TO CHECK ORDER OF AXIES, instead of printing Axie 1 or 2
        if(uc_num >= 0 && uc_num <= 3){
            _axie1.cards[uc_num].card_status = Main::card::can_be_chosen;
            cout << "Axie 1: " << _axie1.cards[uc_num].type <<" - dmg:" << _axie1.cards[uc_num].damage <<" - def:"  << _axie1.cards[uc_num].defence << endl;

        } else if(uc_num >= 4 && uc_num <= 7){
            _axie2.cards[uc_num].card_status = Main::card::can_be_chosen;
            cout << "Axie 2: " << _axie2.cards[uc_num-4].type <<" - dmg:"  << _axie2.cards[uc_num-4].damage <<" - def:"  << _axie2.cards[uc_num-4].defence << endl;
        }
    }
    return cards_drawn;
}

//// prints the cards that ARE chosen by player
void Main::PrintChosenCards(Main::player &p) {
    //find cards that are chosen_for_attack and show them for echa axie in the player
    for (int i = 0; i < 4; ++i) {
        if(p.axies[0].cards[i].card_status == Main::card::chosen_for_attack){
            cout << "Player " << p.id << " Axie 1 card " << p.axies[0].cards[i].id << " is " << p.axies[0].cards[i].type<<" Chosen" << endl;
        }
        if(p.axies[1].cards[i].card_status == Main::card::chosen_for_attack){
            cout << "Player " << p.id << " Axie 2 card " << p.axies[1].cards[i].id << " is " << p.axies[1].cards[i].type<<" Chosen" << endl;
        }
    }
}

//// returns Axies sorted by speed, fastest to slowest
std::vector<Main::axie> Main::sort_axies(player &playa1, player &playa2){
    std::vector<Main::axie> axies_to_sort;
    for (auto &axie : playa1.axies)
        axies_to_sort.push_back(axie);

    for (auto &axie : playa2.axies)
        axies_to_sort.push_back(axie);

    std::sort(axies_to_sort.begin(), axies_to_sort.end(), [](const Main::axie &a, const Main::axie &b) {
        return a.speed > b.speed;
    });
    return axies_to_sort;
}


//// returns the position for each axie as a string
string Main::axiePosition(axie &axie, bool is_first, string stats){
    string pos;
    if (is_first){
        if (axie.position == Main::axie::front){
            pos = "          |"+ stats +"";
        } else {
            pos = ""+ stats +"|          ";
        }
    } else {
        if (axie.position == Main::axie::front){
            pos = ""+stats+"|          ";
        } else {
            pos = "          |"+ stats+ "";
        }
    }
    return pos;
}

//// returns all axies on the board as a string
string Main::printAxies(player &playa1, player &playa2, vector<axie> axies){
    string first_axie, second_axie, third_axie, fourth_axie;
    for (int i = 0; i < 4; i++){
        stringstream s_position, s_health;
        s_position << i + 1;
        s_health << axies[i].health;

        if(playa1.axies[0].id == axies[i].id)
            first_axie = axiePosition(axies[i], true, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa2.axies[0].id == axies[i].id)
            second_axie = axiePosition(axies[i], false, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa1.axies[1].id == axies[i].id)
            third_axie = axiePosition(axies[i], true, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa2.axies[1].id == axies[i].id)
            fourth_axie = axiePosition(axies[i], false, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
    }
    return first_axie + "     " + second_axie + "\n" + third_axie + "     " + fourth_axie;
}

//// prints the game board with Round, Energy and all axies
void Main::PrintGameBoard(Main::player &playa1, Main::player &playa2, int round) {
        // sort axies
        Main main;

        vector<Main::axie> axies = main.sort_axies(playa1, playa2);

        cout << "Round: " << round << " - (attack order : type : health)" << endl;
        cout << "Energy: " << playa1.energy << endl;
        cout << "   back   |           front          |   back" << endl;
        cout << main.printAxies(playa1, playa2, axies) << endl;
    }

//// Card selection state
class Card_Selection_State: public State {
public:
    void UpdateState()  override{
        cout << "Cards are selected!"<< endl;
    };

    void SelectCards(Main::player &player){
        Main main;
        // print the cards that are available to chose for attack
        vector<int> cards_drawn = main.showCardsDrawn(player);
        int input;
        cout << "Choose cards, enter 0 to skip " << endl;

        //// what if player has saved energy? can he spend too many cards at once?
        for (int i = 0; i < player.energy; ++i) {
            cin >>input;
            if (input == 0)
                break;
            if (input == 1){
                if (cards_drawn[0] <= 3){
                    player.axies[0].cards[cards_drawn[0]].card_status = Main::card::chosen_for_attack;
                }
                else if (cards_drawn[0] >= 4 && cards_drawn[0] <= 7){
                    player.axies[1].cards[cards_drawn[0] - 4].card_status = Main::card::chosen_for_attack;
                }
            } else if (input == 2){
                if (cards_drawn[1] <= 3){
                    player.axies[0].cards[cards_drawn[1]].card_status = Main::card::chosen_for_attack;
                }
                else if (cards_drawn[1] >= 4 && cards_drawn[1] <= 7){
                    player.axies[1].cards[cards_drawn[1] - 4].card_status = Main::card::chosen_for_attack;
                }
            } else if (input == 3){
                if (cards_drawn[2] <= 3){
                    player.axies[0].cards[cards_drawn[2]].card_status = Main::card::chosen_for_attack;
                }
                else if (cards_drawn[2] >= 4 && cards_drawn[2] <= 7){
                    player.axies[1].cards[cards_drawn[2] - 4].card_status = Main::card::chosen_for_attack;
                }
            } else if (input == 4){
                if (cards_drawn[3] <= 3){
                    player.axies[0].cards[cards_drawn[3]].card_status = Main::card::chosen_for_attack;
                }
                else if (cards_drawn[3] >= 4 && cards_drawn[3] <= 7){
                    player.axies[1].cards[cards_drawn[3] - 4].card_status = Main::card::chosen_for_attack;
                }
            }
        }
        main.PrintChosenCards(player);
    };

    // Constructor
    Card_Selection_State(Main::player &p1, Main::player &p2){
        Main main;
        main.PrintChosenCards(p1);
//        cout << "Card_Selection_State is created!" << endl;
        cout << "----------------------------------------------------" << endl;
        main.PrintGameBoard(p1, p2, 1);
        cout << "----------------------------------------------------" << endl;
        SelectCards(p1);
        cout << "----------------------------------------------------" << endl;
        SelectCards(p2);

    }
    ~Card_Selection_State(){
        cout << "Card_Selection_State is discarded" << endl;
    };
};

//// Attack state
class Attack_State: public State{
public:
    void UpdateState() override{
        cout << "attack done" << endl;
    }
    void PrintPlayer(Main::player &p1, Main::player &p2){
        Main main;
        main.PrintGameBoard(p1, p2, 1);
//        cout << "Player1: " << p1.axies->cards[0].card_status << endl;
//        cout << "Player2: "<< p2.axies->type << endl;
    }

    // Constructor
    Attack_State(Main::player &p1, Main::player &p2){
        cout << "Attack_State is created" << endl;
        //PrintPlayer(p1,p2);
        BattleClass battleclass;
        battleclass.battle(p1, p2);
        // call transition function

    }

    ~Attack_State(){
        cout << "Attack_State is discarded!" << endl;
    };
};

//// State Controller
class StateController{
private:
    State* currentState = nullptr;

public:
    void Init(Main::player &p1, Main::player &p2){
        currentState = new Card_Selection_State(p1,p2);
    }

    void Update(){
        currentState->UpdateState();
    }

    void TransitionTo (string c, Main::player &p1, Main::player &p2){
        delete currentState;

        if(c == "attack"){
            currentState = new Attack_State(p1, p2);
        }
        if(c == "choose cards"){
            currentState = new Card_Selection_State(p1, p2);
        }
    }

    ~StateController(){
        delete currentState;
    }
};

//// Create player with axies and cards, reads from JSON file.
Main::player Main::createPlayer(int team_id){
    ifstream file("../../axie_teams.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(file, obj);

    stringstream ss;
    string extra = "";
    ss << team_id;
    if (team_id <= 9)
        extra ="0";

    Json::Value team = obj["Team-" + extra + ss.str()];
    Main::player player;

    // json_counter is 1 because we start axie_num with 0, and Axie in the Json start with 1
    for (int axie_num = 0, json_counter = 1; axie_num < 2 ; ++axie_num, json_counter++) {
        player.energy = 2;
        player.id = team["Team-id"].asInt();
        string json_team = "Axie-0" + to_string(json_counter);

        // set axie id, type, health (calcultated), speed, skille, morale
        player.axies[axie_num].id = team[json_team]["Axie-id"].asInt();
        player.axies[axie_num].type = team[json_team]["Type"].asString();
        player.axies[axie_num].health = team[json_team]["Health"].asInt() * 6 + 150;
        player.axies[axie_num].speed = team[json_team]["Speed"].asInt();
        player.axies[axie_num].skill = team[json_team]["Skill"].asInt();
        player.axies[axie_num].morale = team[json_team]["Morale"].asInt();
        if (team[json_team]["Placement"].asString() == "back"){
            player.axies[axie_num].position = Main::axie::position::back;
        }

        // loads two cards for each axie
        for (int card_num = 0; card_num < 2; ++card_num) {
            player.axies[axie_num].cards[card_num].type = team[json_team]["Cards"][card_num]["type"].asString();
            player.axies[axie_num].cards[card_num].name = team[json_team]["Cards"][card_num]["name"].asString();
            player.axies[axie_num].cards[card_num].damage = team[json_team]["Cards"][card_num]["attack"].asInt();
            player.axies[axie_num].cards[card_num].defence = team[json_team]["Cards"][card_num]["defence"].asInt();

            // player.axies[axie_num].cards[card_num].card_status = Main::card::wait_for_restock;
        }

        // Copies the two loaded cards to give each axie 4 cards
        player.axies[axie_num].cards[2] = player.axies[axie_num].cards[0];
        player.axies[axie_num].cards[3] = player.axies[axie_num].cards[1];

        int num = 0;
        if (axie_num == 1) {
            num = 4;
        }

        for (int k = 0; k < 4; ++k) {
            player.axies[axie_num].cards[k].id = k + num;
        }
    }
    return player;
}


// create a function that checks if all cards card_status for each axie is chosen_for_attack if true,
// then change the card_status to wait_for_restock

int main() {
    vector<Main::player> players;
    Main main;
    StateController stateController;

    // ask user to choose Axie teams
    for (int i = 0; i < 2; i++) {
        int axie_team;
        cout << "Choose your axie team: (1-20)" << endl;
        cin >> axie_team;
        players.push_back(main.createPlayer(axie_team));
    }

    stateController.Init(players[0], players[1]);
    int game_round = 1;


    string str = "choose cards";
    while (game_round != 0){
        stateController.Update();

        // stateConroller.TransitionTo returns value 0 if game is over
        stateController.TransitionTo(str, players[0], players[1]);

        if (str == "attack"){
            str = "choose cards";
        } else if (str == "choose cards") {
            str = "attack";
            game_round++;
        }
    }
    return 0;
}