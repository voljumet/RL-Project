#include <vector>
#include <pybind11/pybind11.h>  /// NEEDS TO BE INCLUDED BEFORE THE REST
#include <pybind11/stl.h> /// THIS IS NEEDED FOR CONVERSION BETWEEN CPP-VECTOR AND PYTHON-ARRAY
#include "conversion.cpp"
#include "Main.cpp"

namespace py = pybind11;


vector<int> ChooseTeam(int input){
    Conv conv;
    Main main;
    Main::player playerToSend = main.createPlayer(input);
    return conv.convert_to_vec(playerToSend);
}


vector<int> lilbits(int input, int size){
    Conv conv;
    return conv.convert_to_bits(input, size);
}


struct PState {
    Main main;
    PState(const int &playerChoice_1, const int &playerChoice_2) : player1(main.createPlayer(playerChoice_1)), player2(main.createPlayer(playerChoice_2)) { }
    Conv conv;
    BattleClass battleClass;

    void chooseCards(int player, vector<int> input){
        if (player == 1) 
            main.SelectCards(player1, input);
        else if (player == 2) 
            main.SelectCards(player2, input);
    }
    
    void attack(){
        battleClass.battle(player1, player2);
    }

    void setName(const std::string &name_) { player1.axies[0].type = name_; }
    const std::string &getName() const { return player1.axies[0].type; }

    vector<int> playerMat(int input) {
        if (input == 1) 
            return conv.convert_to_vec(player1);
        else if (input == 2) 
            return conv.convert_to_vec(player2);
    }

    vector<int> playerMatTEST(int input) {
        if (input == 1) 
            return conv.convert_to_vec_TEST(player1);
        else if (input == 2) 
            return conv.convert_to_vec_TEST(player2);
    }
    
    Main::player player1;
    Main::player player2;
};

PYBIND11_MODULE(libjuice, m){
    m.def("ChooseTeam", &ChooseTeam);

    m.def("lilbits", &lilbits);

    py::class_<PState>(m, "PState")
        .def(py::init<const int &, const int &>())

        .def("attack", &PState::attack)
        .def("chooseCards", &PState::chooseCards)
        .def("playerMat", &PState::playerMat)
        .def("playerMatTEST", &PState::playerMatTEST)

        .def("getName", &PState::getName)
        ;

}
