#include <iostream>
#include "BattleClass.cpp"

using namespace std;


class conv {
public:

    int conv_type(string type){
        //create cases for the types plant, aqua and beast and return int 0, 1 or 2
        if(type == "plant"){
            return 0;
        }
        else if(type == "aqua"){
            return 1;
        }
        else if(type == "beast"){
            return 2;
        }
    }

    // merge to vectors
    vector<int> merge_vectors(vector<int> &vector1, vector<int> vector2){
        vector<int> returnVector;

        for(int i : vector1){
            returnVector.push_back(i);
        }

        for(int i : vector2){
            returnVector.push_back(i);
        }

        return returnVector;
    }

    int convert_to_bits(int number, int size){
        int a[10], n, i;
        cout<<"Enter the number to convert: ";
        cin>>n;
        for(i=0; n>0; i++){
            a[i]=n%2;
            n= n/2;
        }
        cout<<"Binary of the given number= ";
        for(i=i-1 ;i>=0 ;i--){
            cout<<a[i];
        }
    }

    // create a function that converts a card into a vector of ints
    vector<int> card_conv(Main::card &card){
        vector<int> returnVector;

        returnVector.push_back(card.card_status);
        returnVector.push_back(conv_type(card.type));
        returnVector.push_back(card.damage);
        returnVector.push_back(card.defence);

        return returnVector;
    }

    vector<int> axie_conv(Main::axie &axie){
        vector<int> returnVector1, returnVector2;

//        returnVector.push_back(axie.strenght); /// does not work, it will be based on card and attacker
        returnVector1 = card_conv(axie.cards[3]);
        returnVector2 = merge_vectors(returnVector1, card_conv(axie.cards[2]));
        returnVector1 = merge_vectors(returnVector2, card_conv(axie.cards[1]));
        returnVector2 = merge_vectors(returnVector1, card_conv(axie.cards[0]));
        returnVector2.push_back(conv_type(axie.type));
        returnVector2.push_back(axie.position);
        returnVector2.push_back(axie.alive);
        returnVector2.push_back(axie.speed);
        returnVector2.push_back(axie.health);

        return returnVector1;
    }

    vector<int> convert_to_vec(Main::player &playa){
        vector<int> returnVector1, returnVector2;
        Main::axie axie;
        returnVector1 = axie_conv(playa.axies[1]);
        returnVector2 = merge_vectors(returnVector1, axie_conv(playa.axies[0]));
        returnVector2.push_back(playa.energy);
        returnVector2.push_back(playa.rank);

        return returnVector2;
    }

};