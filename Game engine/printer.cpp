////
//// Created by alex on 13/04/2022.
////
//
//#include "printer.h"
//
//std::vector<axie> make_list(player &playa1, player &playa2){
//    std::vector<axie> unsorted_axies;
//    for (auto & axie : playa1.axies) {
//        unsorted_axies.push_back(axie);
//    }
//
//    for (auto & axie : playa2.axies) {
//        unsorted_axies.push_back(axie);
//    }
//
//    // create mapping between speed and id
//    std::map<int, int> speed_id;
//    for (auto & i : unsorted_axies) {
//        speed_id[i.speed] = i.id;
//    }
//
//    vector<std::pair<int, int> > arr;
//    for (const auto &item : speed_id) {
//        arr.emplace_back(item);
//    }
////    sort
//    std::sort(arr.begin(), arr.end(),
//              [] (const auto &x, const auto &y) {return x.second < y.second;});
//
//    std::vector<axie> sorted_axies;
//    for (int j = 0; j < arr.size(); ++j) {
//        for (int k = 0; k < unsorted_axies.size(); ++k) {
//            if (arr[j].second == unsorted_axies[k].id) {
//                sorted_axies.push_back(unsorted_axies[j]);
//            }
//        }
//    }
//
//
//    return sorted_axies;
//}
//
//
//void printer(player &playa1, player &playa2, int round){
//    cout << "Round: " << round << endl;
//    // create vector from player
//    vector<axie> axies;
//
//
//    //pint axie placement on top
//    cout << "Round: " << round << endl;
//    std::vector<axie> axie_speed;
//
//    make_list(playa1, playa2);
//
//    for (int i = 0; i < 3; i++){
//        if (playa1.axies[i].speed >= axie_speed[0].speed){
//            axie_speed.push_back(playa1.axies[i]);
//        }
//
//    }
////        speed.append(playa.axies[i].speed);
//
//
//
//    // function to add axies to vector based on speed
//
//
//    // print axie states + placements
////    cout << "Player " << playa.id << ":" << endl;
//
//    // print energy
//
//    // print
//
//}