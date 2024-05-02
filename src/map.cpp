#include "include/map.hpp"

#include <iostream>
#include <cmath>


Map::Map(std::string _filepath) : height{0}, width{0} {
    build_map(_filepath);
}

void Map::build_map(std::string _filepath){
    FILE *f = fopen(_filepath.c_str(), "r");
	if (!f){
		printf("Opening file failed! \n");
		throw std::runtime_error("Opening map file failed!");
	}
	int file_args = fscanf(f, "height %d\nwidth %d\n", &this->height, &this->width);

	if (file_args != 2) {
		throw std::runtime_error("Invalid loadMap parsing map metadata");
	}
	
	for (int _y = 0; _y < this->height; _y++) {
		std::vector<int> row;
		for (int _x = 0; _x < this->width; _x++) {
			char c;
			do {
				if (fscanf(f, "%c", &c) != 1) {
					throw std::runtime_error("Invalid parsing");
				}
			} while (isspace(c));
			
			if (!(c == '0')) { 
				row.push_back(1);
			}			
			else {
				row.push_back(0);
			}
		}
		this->map.push_back(row);
	}
	fclose(f);
}

std::pair<int, int> Map::get_size(){
	return std::make_pair(height, width);
}

void Map::print_map(){
	std::cout << "Map: " << std::endl;
	int n = this->map.size();
	int m = this->map[0].size();
	
	for(auto row : this->map){
		for(auto el : row)
			std::cout << el << " ";
		std::cout << std::endl;
		
	}
}