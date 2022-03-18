#include <iostream>
#include <chrono>
#include <vector>

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
    int bodypart_1 [2] = {0,0};
    int bodypart_2 [2] = {0,0};
    enum position {front,rear};
    card cards[2];
};

struct player{
    unsigned int id = 0;
    axie axies [2];
    unsigned int energy = 0; // allows player to use skills
    unsigned int rank = 0; // rank of player
};

struct card{
    string type = "";
    int damage = 0;
    int defence = 0;
    enum status {usable, unusable};
};

player createPlayer(int axie1, int axie2){
    player p;
//    lookup axies from database

    p.axies[0].type = "plant";

    return p;
}

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

void gameloop(){
    int axies [2];
    cin >> axies[0] >> axies[1];
    player player1 = createPlayer(111,222);
    player player2 = createPlayer(444,555);

//    check speed of axies to set turn order

    std::vector<int> turnOrder = sortTurnOrder(player1, player2);


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

int main() {
    gameloop();

    int i = 1;
    auto start = high_resolution_clock::now();
    while (i < 1000000){
        if(i % 100 == 0){
            i = i + 1;
        }
        printf("%i\n",i);
        i++;
    }

    auto stop = high_resolution_clock::now();
    cout << "Time taken by function: " << float(duration_cast<microseconds>(stop - start).count())/1000000.0 << " seconds" << endl;
    return 0;
}
