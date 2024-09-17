#include <memory>

#include "include/astar.hpp"

AStar::AStar(Map& map, Pair& start, Pair& goal) 
                        :  map_(map), foundPath(false), collision_threshold(1){
    map_size = map_.get_size();
    start_ = std::make_shared<Node>(start.first, start.second, 
                                    0.0, 0.0, 0.0, nullptr);
    goal_ = std::make_shared<Node>(goal.first, goal.second, 
                                    0.0, 0.0, 0.0, nullptr);
}

double AStar::getG(int x, int y){
    return map_.map[x][y];
}

// Euclidean distance heuristic
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

void AStar::Plan(){
    std::cout << "Start planning ... " << start_->x_ << " " << start_->y_ << std::endl;

    open_list.push(start_);
    open_list_lookup.insert({std::make_pair(start_->x_, start_->y_), start_->f_});
    
    while(!open_list.empty() && !foundPath){
        std::shared_ptr<Node> current_node = open_list.top();
        open_list.pop();
        open_list_lookup.erase(std::make_pair(current_node->x_, current_node->y_));

        // if open list top is the goal then goal is reached
        // TODO: Refine
        if((goal_->x_ == current_node->x_) && (goal_->y_ == current_node->y_)){
            std::cout << "Path to goal is found" << std::endl;
            foundPath = true;
            backtrack(current_node);

            break;
        }

        if(closed_list.find(std::make_pair(current_node->x_, current_node->y_)) != closed_list.end())
           continue;
        else{    
            auto pose = std::make_pair(current_node->x_, current_node->y_);
            closed_list.insert({pose, current_node});
            Visited.push_back(pose);
        }

         for(int i=0; i<NUM_DIRS; i++){
            
            int sX = current_node->x_ + dX[i];
            int sY = current_node->y_ + dY[i];
            if (isValid(sX, sY) && isCollisionFree(sX, sY)){

                if(closed_list.find(std::make_pair(sX, sY))!=closed_list.end()){
                    continue;
                }

                double newG = current_node->g_ + getG(sX, sY);            
                double newH = calcHeuristic(sX, sY);
                double newF = newG + newH;

                auto succesor = std::make_shared<Node>(sX, sY, newG, newH, newF, current_node);

                if(open_list_lookup.find(std::make_pair(succesor->x_, succesor->y_))!=open_list_lookup.end()){
                    if(open_list_lookup[std::make_pair(succesor->x_, succesor->y_)] < succesor->f_){
                        continue;
                    }
                    else{
                        open_list.push(succesor);
                        open_list_lookup[std::make_pair(succesor->x_, succesor->y_)] = succesor->f_;
                    }
                }
                else{
                    open_list.push(succesor);
                    open_list_lookup.insert({std::make_pair(succesor->x_, succesor->y_), succesor->f_});
                }
            }
        }
    }

    if (!foundPath)
        std::cout << "Path not found" << std::endl;
}

void AStar::backtrack(std::shared_ptr<Node>& last_node){
    while(last_node->parent_ != nullptr){
        Path.push_back(std::make_pair(last_node->x_, last_node->y_));
        last_node = (last_node->parent_);
    }
    printf("Start [%d %d] -> Goal [%d %d]\n", Path.back().first, Path.back().second, Path.front().first, Path.front().second);
    std::reverse(Path.begin(), Path.end());
}

void AStar::print_plan(){
    std::cout << "A Star path plan" << std::endl;

    for(auto p : Path){
        printf(" [%d %d] -> \n", p.first, p.second);
    }
}