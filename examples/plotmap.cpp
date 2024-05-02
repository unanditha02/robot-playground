#include <iostream>

// #include "matplotlibcpp.h"
#include "../src/planner/include/map.hpp"

// namespace plt = matplotlibcpp;

int main(int argc, char** argv) {

    try{
        Map mymap(argv[1]);
        std::cout << argv[1] << std::endl;
        mymap.print_details();
        mymap.print_map();

        printf("The map is loaded\n");
    }

    catch(const std::exception& e){
        std::cout << "ERROR!!!" << std::endl;
    }
    

    return 0;
}