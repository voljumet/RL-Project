#include <iostream>
#include "BattleClass.cpp"

using namespace std;


class conv {
public:

    int convert_str_to_int(string type){
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
        for(int i : vector1)
            returnVector.push_back(i);

        for(int i : vector2)
            returnVector.push_back(i);

        return returnVector;
    }

    vector<int> convert_to_bits(int number, int size){
        int a[size], i;
        vector <int> returnVector1, returnVector2;

        for(i = 0; number > 0; i++){
            a[i] = number % 2;
            number = number / 2;
        }

        for(i=i-1 ;i>=0 ;i--)
            returnVector1.push_back(a[i]);

        while (returnVector1.size()+returnVector2.size() < size)
            returnVector2.push_back(0);

        return merge_vectors(returnVector2,returnVector1);
    }

    // create a function that converts a card into a vector of ints
    vector<int> card_conv(Main::card &card){
        vector<int> returnVector1, returnVector2;

        returnVector1 = convert_to_bits(card.card_status, 2);
        returnVector2 = merge_vectors(returnVector1, convert_to_bits(convert_str_to_int(card.type),2));
        returnVector1 = merge_vectors(returnVector2, convert_to_bits(card.damage,8));
        returnVector2 = merge_vectors(returnVector1, convert_to_bits(card.defence,7));

        return returnVector2;
    }

    vector<int> axie_conv(Main::axie &axie){
        vector<int> returnVector1, returnVector2;

        returnVector1 = card_conv(axie.cards[3]);
        returnVector2 = merge_vectors(returnVector1, card_conv(axie.cards[2]));
        returnVector1 = merge_vectors(returnVector2, card_conv(axie.cards[1]));
        returnVector2 = merge_vectors(returnVector1, card_conv(axie.cards[0]));
        returnVector1 = merge_vectors(returnVector2, convert_to_bits(convert_str_to_int(axie.type),2));
        returnVector1.push_back(axie.position);
        returnVector1.push_back(axie.alive);
        returnVector2 = merge_vectors(returnVector1, convert_to_bits(axie.speed,6));
        returnVector1 = merge_vectors(returnVector2, convert_to_bits(axie.health,10));

        return returnVector1;
    }

    vector<int> convert_to_vec(Main::player &playa){
        vector<int> returnVector1, returnVector2;
        Main::axie axie;
        returnVector1 = axie_conv(playa.axies[1]);
        returnVector2 = merge_vectors(returnVector1, axie_conv(playa.axies[0]));
        returnVector1 = merge_vectors(returnVector2, convert_to_bits(playa.energy,4));
        returnVector2 = merge_vectors(returnVector1, convert_to_bits(playa.rank,12)); /// can achieve rank 4096

        return returnVector2;
    }

};