#pragma once
#include <vector>
#include <memory>

#define PI 3.141592654

using std::vector;
using std::shared_ptr;



struct Node{

    int x_, y_, t_;

    shared_ptr<Node> parent_;
    double g_, f_, h_;

    Node(const int& x, const int& y, const int& t, const double& g, const double& h, const double& f, const shared_ptr<Node>& parent) :
        x_{x}, y_{y}, t_{t}, g_{g}, h_{h}, f_{f}, parent_{parent}{};
};