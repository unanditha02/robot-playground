#include <math.h>
#include <string.h>

#include <vector>
#include <algorithm>
#include <iostream>

#include <memory>
#include <queue>
#include <unordered_map>

#include "node.hpp"
#include "map.hpp"


#define NUM_DIRS 8

typedef std::pair<int, int> Pair;

struct hash_pair{
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const{
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

// sort for priority queue
struct lowestF{
    bool operator()(const std::shared_ptr<Node> &a, const std::shared_ptr<Node> &b){
        return a->f_ > b->f_;
    }
};

class AStar{
    private:
        Pair map_size;
        int collision_threshold;
        
        Map map_;
        
        std::shared_ptr<Node> start_;
        std::shared_ptr<Node> goal_;

        int dX[NUM_DIRS] = {-1, -1, -1,  0,  0,  1, 1, 1};
        int dY[NUM_DIRS] = {-1,  0,  1, -1,  1, -1, 0, 1};

        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, lowestF> open_list;
        std::unordered_map<Pair, int, hash_pair> open_list_lookup;
        std::unordered_map<Pair, std::shared_ptr<Node>, hash_pair> closed_list;

        bool isValid(int x, int y);
        bool isCollisionFree(int x, int y);

        double getG(int x, int y);
        double calcHeuristic(int x, int y);
        void calcPlanningTime();

    public:
        bool foundPath;
        std::vector<Pair> Path;
        std::vector<Pair> Visited;

        // TODO: map size, collision threshold to added to constructor
        AStar(Map& map, Pair& start, Pair& goal);
        void Plan();
        void backtrack(std::shared_ptr<Node> &last_node);
        void print_plan();

};



