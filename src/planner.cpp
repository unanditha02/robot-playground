#include <math.h>
#include <time.h>
#include <fstream>

#include "include/astar.hpp"
#include "include/map.hpp"

int main(int argc, char** argv) {
	
	try{
			clock_t time_begin;
			clock_t time_end;

			// load map
			// TODO: Use pointers 
			std::string _filepath;
			_filepath = "resources/map_basic.txt";
			
			Map mymap(_filepath);
			mymap.print_map();

			// set start and goal poses
			// auto start = std::make_pair(10, 10);	// -y, x
			// auto goal = std::make_pair(18, 10); 

			auto start = std::make_pair(10, 10);	// -y, x
			auto goal = std::make_pair(18, 20); 

			// create planner object and plan path
			AStar myplanner(mymap, start, goal);

			// TODO: Clean up time calculation
			time_begin = clock();
			// planning 
			myplanner.Plan();
			time_end = clock();	
			std::cout << "A Star Planner: " << double(time_end - time_begin) / CLOCKS_PER_SEC << " seconds" << std::endl;
			
			// print plan
			myplanner.print_plan();

			// write to file
			std::string result_path;
			result_path = "resources/path.txt";

			std::ofstream myfile;
			myfile.open (result_path);
			for(auto p : myplanner.Path){
				myfile << p.first << " " << p.second << "\n";
			}
			
			myfile.close();

			// TODO: read and plot
		}

		catch(const std::exception& e){
			std::cout << "ERROR!!!" << std::endl;
		}
    
	
}