#include "QuadTree.h"

using namespace std;

QuadTree::QuadTree(int size){
    root = new Node(Point(0,0), Point(size-1, size-1));
    numPoints = 0;
}

int QuadTree::totalPoints(){
    return numPoints;
}

int QuadTree::totalNodes(){
    return  root->numNodes();
}

void QuadTree::insert(Point p, int population){
    if(root->insert(p,population)){
        numPoints++;
    }
}

void QuadTree::search(Point p){
    if(root->search(p)!=NULL)
        cout<<"DATO BUSCADO:"<<root->search(p)->population<<endl;
}

vector<Data> QuadTree::list(){
    return root->list();
}

int QuadTree::countRegion(Point p, int d) {
    return root->countRegion(p, d);
}

int QuadTree::AggregateRegion(Point p, int d) {
    return root->AggregateRegion(p, d);
}

