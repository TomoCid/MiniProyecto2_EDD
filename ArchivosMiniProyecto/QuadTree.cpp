#include "QuadTree.h"

using namespace std;

QuadTree::QuadTree(int size){
    root = new Node(Point(0,0), Point(size, size));
    numPoints = 0;
}

int QuadTree::totalPoints(){
    return numPoints;
}

int QuadTree::totalNodes(){
    return root->numNodes();
}

void QuadTree::insert(Point p, int data, string cityname, string country){
    if(root->insert(p, data, cityname, country)){
        numPoints++;
    }
}

vector<Data> QuadTree::list(){
    return root->list();
}

int QuadTree::countRegion(Point p, int d) {
    return root->countRegion(p, d);
}

long long QuadTree::AggregateRegion(Point p, int d) {
    return root->AggregateRegion(p, d);
}

