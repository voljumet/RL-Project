#include <vector>
#include <pybind11/pybind11.h>  /// NEEDS TO BE INCLUDED BEFORE THE REST
#include <pybind11/stl.h> /// THIS IS NEEDED FOR CONVERSION BETWEEN CPP-VECTOR AND PYTHON-ARRAY
#include "conversion.cpp"
#include "Main.cpp"


namespace py = pybind11;



int add(int a, int b){
	return a + b;
}
int sub(int a, int b){
	return a - b;
}
int mult(int a, int b){
	return a * b;
}


vector<int> CreatePlayerVec(int input){
    conv conv;
    Main main;
    Main::player playerToSend = main.createPlayer(input);
    return conv.convert_to_vec(playerToSend);
}


PYBIND11_MODULE(libjuice, m){
	m.def("add", &add);
	m.def("sub", &sub);
	m.def("mult", &mult);
    m.def("cpv", &CreatePlayerVec);

}