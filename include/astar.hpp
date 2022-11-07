#include <math.h>
#include <string.h>

#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>

#include "../include/node.hpp"

#define NUM_DIRS 8

using std::vector;
using std::pair;
using std::priority_queue;
using std::unordered_map;

typedef pair<int, int> Pair;

struct hash_pair{
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const{
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;             
        }
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

// sort for priority queue
struct lowestF{
    bool operator()(const shared_ptr<Node> &a, const shared_ptr<Node> &b){
        return a->f_ > b->f_;
    }
};

namespace astar{

    class AStar{
        private:
            Pair map_size;
            int collision_threshold;

            shared_ptr<Node> start_;
            shared_ptr<Node> goal_;
    
            int dX[NUM_DIRS] = {-1, -1, -1,  0,  0,  1, 1, 1};
            int dY[NUM_DIRS] = {-1,  0,  1, -1,  1, -1, 0, 1};

            priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, lowestF> open_list;
            unordered_map<Pair, int, hash_pair> open_list_lookup;
            unordered_map<Pair, shared_ptr<Node>, hash_pair> closed_list;

            bool isValid(int x, int y);
            bool isCollisionFree(int x, int y);

            double getG(int x, int y);
            double calcHeuristic(int x, int y);

            void calcPlanningTime();

        public:
            bool foundPath;
            vector<Pair> Path;
            // TODO: map size, collision threshold to added to constructor
            AStar(shared_ptr<Node> start, shared_ptr<Node> goal);
            void AStar_Planner();

            void backtrack(shared_ptr<Node> &last_node);
    };


}


