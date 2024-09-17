#include <math.h>
#include <time.h>
#include <fstream>

#include "include/astar.hpp"
#include "include/map.hpp"

int main(int argc, char** argv) {
	
	std::string map_filepath = argv[1];
	std::string result_filepath = argv[2];
	auto start = std::make_pair(std::stoi(argv[3]), std::stoi(argv[4])); 	// std::make_pair(10, 10);	// -y, x
	auto goal = std::make_pair(std::stoi(argv[5]), std::stoi(argv[6]));		// std::make_pair(25, 40)
	
	try{
		clock_t time_begin;
		clock_t time_end;

		// load map
		// TODO: Use pointers 
		Map mymap(map_filepath);

		// create planner object and plan path
		AStar myplanner(mymap, start, goal);

		// TODO: Clean up time calculation
		time_begin = clock();

		// planning 
		myplanner.Plan();
		time_end = clock();	
		std::cout << "A Star Planner: " << double(time_end - time_begin) / CLOCKS_PER_SEC << " seconds" << std::endl;
		
		// write to file
		std::ofstream myfile;
		myfile.open (result_filepath);
		for(auto p : myplanner.Path){
			myfile << p.first << " " << p.second << "\n";
		}
		// TODO: Plot visited cells
		// for(auto p : myplanner.Visited){
		// 	myfile << p.first << " " << p.second << "\n";
		// }
		myfile.close();
		// TODO: read and plot
	}

	catch(const std::exception& e){
		std::cout << "ERROR!!!" << std::endl;
	}
    
}