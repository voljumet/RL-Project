#include <iostream>
#include <vector>
#include <fstream>
#include <json/json.h>
#include "main.h"


/////////////////////////////////////////////////////////////////////////////////////////////////
// funtion that select four random numbers between 0 and 7, and a number can not be repeated
// if the number is repeated, it will be replaced by another number
// the number of numbers will be 4 and the range is 0 to 7
// the function will return a vector of 4 numbers
vector<int> selectFourNumbers(){
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


vector<int> showAvailabeCards(main::player &p) {
    vector<int> usableCards = selectFourNumbers();
    // check if the number is between 0 and 3, if so find the card that have the same card id

    for (int i = 0; i < 4; ++i) {
        if(usableCards[i] >= 0 && usableCards[i] <= 3){
            p.axies[0].cards[usableCards[i]].status = main::card::usable;
            cout << "Player " << p.id << " Axie 1 card " << usableCards[i] << " is " << p.axies[0].cards[usableCards[i]].type << endl;
        }
        else if(usableCards[i] >= 4 && usableCards[i] <= 7){
            p.axies[1].cards[usableCards[i]].status = main::card::usable;
            cout << "Player " << p.id << " Axie 2 card " << usableCards[i] << " is " << p.axies[1].cards[usableCards[i] - 4].type << endl;
        }
    }
    return usableCards;
}

void showUsedCards(main::player &p) {
    //find cards that are used and show them for echa axie in the player
    for (int i = 0; i < 4; ++i) {
        if(p.axies[0].cards[i].status == main::card::used){
            cout << "Player " << p.id << " Axie 1 card " << p.axies[0].cards[i].id << " is " << p.axies[0].cards[i].type<<" Chosen" << endl;
        }
        if(p.axies[1].cards[i].status == main::card::used){
            cout << "Player " << p.id << " Axie 2 card " << p.axies[1].cards[i].id << " is " << p.axies[1].cards[i].type<<" Chosen" << endl;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



class Card_Selection_State: public State {
public:
    void UpdateState()  override{
        cout << "Cads are selected!"<< endl;
    };

    void SelectCards(main::player &p1, main::player &p2){
        //print the cards that are available to pick from
        vector<int> randomSelectCards =  showAvailabeCards(p1);
        int input;
        cout << "Choose cards for player 1 !" << endl;
        for (int i = 0; i < p1.energy; ++i) {
            cin >>input;
            if (input == 1){
                if (randomSelectCards[0]<= 3){
                    p1.axies[0].cards[randomSelectCards[0]].status = main::card::used;
                }
                else if (randomSelectCards[0]>= 4 && randomSelectCards[0]<= 7){
                    p1.axies[1].cards[randomSelectCards[0] - 4].status = main::card::used;
                }
            } else if (input == 2){
                if (randomSelectCards[1]<= 3){
                    p1.axies[0].cards[randomSelectCards[1]].status = main::card::used;
                }
                else if (randomSelectCards[1]>= 4 && randomSelectCards[1]<= 7){
                    p1.axies[1].cards[randomSelectCards[1] - 4].status = main::card::used;
                }
            } else if (input == 3){
                if (randomSelectCards[2]<= 3){
                    p1.axies[0].cards[randomSelectCards[2]].status = main::card::used;
                }
                else if (randomSelectCards[2]>= 4 && randomSelectCards[2]<= 7){
                    p1.axies[1].cards[randomSelectCards[2] - 4].status = main::card::used;
                }
            } else if (input == 4){
                if (randomSelectCards[3]<= 3){
                    p1.axies[0].cards[randomSelectCards[3]].status = main::card::used;
                }
                else if (randomSelectCards[3]>= 4 && randomSelectCards[3]<= 7){
                    p1.axies[1].cards[randomSelectCards[3] - 4].status = main::card::used;
                }
            }
        }

        showUsedCards(p1);
        vector<int> randomSelectCards2 =  showAvailabeCards(p2);;
        int input2;
        cout << "Choose cards for player 2 !" << endl;
        for (int i = 0; i < p2.energy; ++i) {
            cin >>input2;
            if (input2 == 1){
                if (randomSelectCards2[0]<= 3){
                    p2.axies[0].cards[randomSelectCards2[0]].status = main::card::used;
                }
                else if (randomSelectCards2[0]>= 4 && randomSelectCards2[0]<= 7){
                    p2.axies[1].cards[randomSelectCards2[0] - 4].status = main::card::used;
                }
            } else if (input2 == 2){
                if (randomSelectCards2[1]<= 3){
                    p2.axies[0].cards[randomSelectCards2[1]].status = main::card::used;
                }
                else if (randomSelectCards2[1]>= 4 && randomSelectCards2[1]<= 7){
                    p1.axies[1].cards[randomSelectCards2[1] - 4].status = main::card::used;
                }
            } else if (input2 == 3){
                if (randomSelectCards2[2]<= 3){
                    p2.axies[0].cards[randomSelectCards2[2]].status = main::card::used;
                }
                else if (randomSelectCards2[2]>= 4 && randomSelectCards2[2]<= 7){
                    p2.axies[1].cards[randomSelectCards2[2] - 4].status = main::card::used;
                }
            } else if (input2 == 4){
                if (randomSelectCards2[3]<= 3){
                    p2.axies[0].cards[randomSelectCards2[3]].status = main::card::used;
                }
                else if (randomSelectCards2[3]>= 4 && randomSelectCards2[3]<= 7){
                    p2.axies[1].cards[randomSelectCards2[3] - 4].status = main::card::used;
                }
            }
        }
        showUsedCards(p2);
    }
    // Constructor
    Card_Selection_State(main::player &p1, main::player &p2){
        cout << "Card_Selection_State is created!" << endl;
        SelectCards(p1, p2);

    }
    ~Card_Selection_State(){
        cout << "Card_Selection_State is discarded" << endl;
    };
};


class Attack_State: public State{
public:
    void UpdateState() override{
        cout << "attack done"  << endl;
    }
    void PrintPlayer(main::player &p1, main::player &p2){
        cout << "Player1: "<< p1.axies->cards[0].status << endl;
        cout << "Player2: "<< p2.axies->type << endl;
    }

    // Constructor
    Attack_State(main::player &p1, main::player &p2){
        cout << "Attack_State is created" << endl;
        p1.id = 30;
        p2.id = 50;
        PrintPlayer(p1,p2);
    }

    ~Attack_State(){
        cout << "Attack_State is discreated!" << endl;
    };
};

class StateController{
private:
    State* currentState = nullptr;

public:
    void Init(main::player &p1, main::player &p2){
        currentState = new Card_Selection_State(p1,p2);
    }

    void Update(){
        currentState->UpdateState();
    }

    void TransitionTo (char c, main::player &p1, main::player &p2){
        delete currentState;
        if(c == 'a'){currentState = new Attack_State(p1, p2);}
        if(c == 'c'){currentState = new Card_Selection_State(p1, p2);}
    }

    ~StateController(){
        delete currentState;
    }
};

void fetch_card(){
    ifstream file("/Users/peshangalo/Documents/Master/First_Year/Second Semester/RL/RL-Project/axie_cards.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(file, obj);
//find attribute name of the JSON obj


}

main::player createPlayer(Json::Value &team){
    main::player p;

    for (int i = 0; i < 2 ; ++i) {
        p.id = i;
        p.energy = 2;
        string axie = "Axie-0";
        axie += to_string(i);
        p.id = team["Team-id"].asInt();
        p.axies[i].id = team["Axie-0"+to_string(i+1)]["Axie-id"].asInt(); // Pluss 1 because we start i with 0, and Axie in the Json file is either 01 or 02
        p.axies[i].type = team["Axie-0"+to_string(i+1)]["Type"].asString();
        p.axies[i].health = team["Axie-0"+to_string(i+1)]["Health"].asInt();
        p.axies[i].speed = team["Axie-0"+to_string(i+1)]["Speed"].asInt();
        p.axies[i].skill = team["Axie-0"+to_string(i+1)]["Skill"].asInt();
        p.axies[i].morale = team["Axie-0"+to_string(i+1)]["Morale"].asInt();
        p.axies[i].cards[0].type = team["Axie-0"+to_string(i+1)]["Cards"][0].asString();
        p.axies[i].cards[1].type = team["Axie-0"+to_string(i+1)]["Cards"][1].asString();
        p.axies[i].cards[2].type = team["Axie-0"+to_string(i+1)]["Cards"][0].asString();
        p.axies[i].cards[3].type = team["Axie-0"+to_string(i+1)]["Cards"][1].asString();

        p.axies[i].cards[0].status = main::card::unusable;
        p.axies[i].cards[1].status = main::card::unusable;
        p.axies[i].cards[2].status = main::card::unusable;
        p.axies[i].cards[3].status = main::card::unusable;

        if ( i == 0){

        p.axies[i].cards[0].id = 0;
        p.axies[i].cards[1].id = 1;
        p.axies[i].cards[2].id = 2;
        p.axies[i].cards[3].id = 3;
        }
        else{
        p.axies[i].cards[0].id = 4;
        p.axies[i].cards[1].id = 5;
        p.axies[i].cards[2].id = 6;
        p.axies[i].cards[3].id = 7;
        }
    }
    return p;
}

// create a function that check if all cards status for each axie is used if true, then change the status to unusable


std::vector<main::axie> sort_axies(main::player &playa1, main::player &playa2){
    std::vector<main::axie> axies_to_sort;
    for (auto & axie : playa1.axies) {
        axies_to_sort.push_back(axie);
    }

    for (auto & axie : playa2.axies) {
        axies_to_sort.push_back(axie);
    }

    // sort map by value
    std::sort(axies_to_sort.begin(), axies_to_sort.end(), [](const main::axie &a, const main::axie &b) {
        return a.speed > b.speed;
    });

    return axies_to_sort;
}

//function that returns multiple strings
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string position(main::axie axie, bool is_first, string stats){
    string pos;
    if (is_first){
        if (axie.position == main::axie::front){
            pos = "          |"+ stats +"";
        } else {
            pos = ""+ stats +"|          ";
        }
    } else {
        if (axie.position == main::axie::front){
            pos = ""+stats+"|          ";
        } else {
            pos = "          |"+ stats+ "";
        }
    }

    return pos;
}

string rest(main::player &playa1, main::player &playa2, vector<main::axie> axies){
    string first,second,third,fourth;
    for (int i = 0; i < 4; i++){
        stringstream s_position, s_health;
        s_position << i + 1;
        s_health << axies[i].health;

        if(playa1.axies[0].id == axies[i].id)
            first = position(axies[i], true, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa2.axies[0].id == axies[i].id)
            second = position(axies[i], false, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa1.axies[1].id == axies[i].id)
            third = position(axies[i], true, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
        else if(playa2.axies[1].id == axies[i].id)
            fourth = position(axies[i], false, s_position.str() + ":" + axies[i].type + ":" + s_health.str());
    }

    string print = "\n"+first +"     "+ second + "\n"+ third +"     "+ fourth;
    return "          |                         |"+print;
}

void printer(main::player &playa1, main::player &playa2, int round){
    cout << "Round: " << round << " - (attack order : type : health)"<< endl;
    cout << "Energy: " << playa1.energy << endl;

    // sort axies
    vector<main::axie> axies = sort_axies(playa1, playa2);

    // print axie states + placements
    cout << rest(playa1, playa2, axies) << endl;
    cout << endl;
}

int main() {
    ifstream file("../../axie_teams.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(file, obj);
    vector<main::player> players;

    // ask user to choose Axie teamzzz
    for (int i = 0; i < 2; i++) {
        int axie_team;
        string team = "";
        cout << "Choose your axie team: (1-20)" << endl;
        cin >> axie_team;
        if (axie_team <= 9)
            team ="0";
        players.push_back(createPlayer(obj["Team-" +team+to_string(axie_team)]));
    }

    printer(players[0], players[1], 1);

    StateController stateController;
    stateController.Init(players[0], players[1]);

    string str = " ";
    while (str[0] != 'q'){
        stateController.Update();
        cout << "Enter q to quit" << endl;
        cout << "Enter a to change to attack state" << endl;
        cout << "Enter c to change to card selection state" << endl;

        cin >> str;

      if (str[0] == 'a' || str[0] == 'c'){stateController.TransitionTo(str[0], players[0], players[1]);}
    }

    return 0;
}