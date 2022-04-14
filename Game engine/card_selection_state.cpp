
#include <iostream>
#include <vector>
#include <fstream>
#include <json/json.h>

vector<int> selectFourNumbers(){
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

vector<int> numbers = selectFourNumbers();
// cout << numbers[0] << " " << numbers[1] << " " << numbers[2] << " " << numbers[3] << endl;