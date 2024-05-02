#pragma once

#include <vector>
#include <memory>

class Map{
    
    void build_map(std::string _filepath);

    public:
        int height, width;

        std::vector<std::vector<int>> map;

        Map(std::string _filepath);
        void print_map();
        std::pair<int, int> get_size();

};