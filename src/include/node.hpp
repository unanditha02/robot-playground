#pragma once
#include <memory>
#include <iostream>
#define PI 3.141592654


struct Point2D{
    public:
        int x_, y_;

        Point2D() : x_(-1), y_(-1){}
        Point2D(int x, int y) : x_(x), y_(y){}

        bool operator==(const Point2D& p){
            return((this->x_ == p.x_) && (this->y_ == p.y_));
        }
};

struct Node{

    int x_, y_;

    std::shared_ptr<Node> parent_;
    double g_, f_, h_;

    Node(const int& x, const int& y, const double& g, const double& h, const double& f, const std::shared_ptr<Node>& parent) :
        x_{x}, y_{y}, g_{g}, h_{h}, f_{f}, parent_{parent}{};

    void print_node(){
        std::cout << "x: " << x_ << "\ty: " << y_ << "\ng: " << g_ << "\th: " << h_ << "\tf: " << f_ << "\nparent: " << parent_ << std::endl;
    }
};