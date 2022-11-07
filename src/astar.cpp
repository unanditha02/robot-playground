#include <memory>

#include "../include/astar.hpp"

// using std::shared_ptr;
using std::make_pair;
using std::make_shared;
using namespace astar;

AStar::AStar(shared_ptr<Node> start, shared_ptr<Node> goal) 
                        :  start_(start),
                            goal_(goal),
                            foundPath(false){

    open_list.push(start_);
    open_list_lookup.insert({make_pair(start_->x_, start_->y_), start_->f_});
}

double AStar::getG(int x, int y){
    // TODO: read from map
    return 0.0;
}

double AStar::calcHeuristic(int x, int y){
    return ((double)sqrt((x - goal_->x_) * (x - goal_->x_) + 
                            (y - goal_->y_) * (y - goal_->y_)));

}

bool AStar::isValid(int x, int y){
    return (x >= 0 && x <= map_size.first && y >= 0 && y <= map_size.second);
}

bool AStar::isCollisionFree(int x, int y){
    if((getG(x, y) >= 0) && (getG(x, y) < collision_threshold))
        return true;
    else
        return false;
}


void AStar::AStar_Planner(){

    while(!open_list.empty()){
        shared_ptr<Node> current_node = open_list.top();
        open_list.pop();
        open_list_lookup.erase(make_pair(current_node->x_, current_node->y_));

        if(closed_list.find(make_pair(current_node->x_, current_node->y_)) != closed_list.end())
            continue;
        else    
            closed_list.insert({make_pair(current_node->x_, current_node->y_), current_node});

         for(int i=0; i<NUM_DIRS; i++){

            int sX = current_node->x_ + dX[i];
            int sY = current_node->y_ + dY[i];

            if (isValid(sX, sY) && isCollisionFree(sX, sY)){

                if(closed_list.find(make_pair(sX, sY))!=closed_list.end()){
                    continue;
                }

                double newG = current_node->g_ + getG(sX, sY) + 0.3*current_node->t_;            
                double newH = calcHeuristic(sX, sY);
                double newF = newG + newH;

                auto succesor = make_shared<Node>(sX, sY, (current_node->t_)+1, newG, newH, newF, current_node);

                if(open_list_lookup.find(make_pair(succesor->x_, succesor->y_))!=open_list_lookup.end()){
                    if(open_list_lookup[make_pair(succesor->x_, succesor->y_)] < succesor->f_){
                        continue;
                    }
                    else{
                        open_list.push(succesor);
                        open_list_lookup[make_pair(succesor->x_, succesor->y_)] = succesor->f_;
                    }
                }
                else{
                    open_list.push(succesor);
                    open_list_lookup.insert({make_pair(succesor->x_, succesor->y_), succesor->f_});
                }
            }
        }
    }
}

void AStar::backtrack(shared_ptr<Node> &last_node){
    printf("Target Cell: [%d %d]\n", last_node->x_, last_node->y_);
    while(last_node->parent_ != nullptr){
        Path.push_back(make_pair(last_node->x_, last_node->y_));
        last_node = (last_node->parent_);
    }
    foundPath = true;
    printf("First [%d %d] -> Last [%d %d]\n", Path.back().first, Path.back().second, Path.front().first, Path.front().second);
}