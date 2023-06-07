#include <cmath>
#include <iostream>
#include "ADTQuadTree.h"
#include "Structs.h"

using namespace std; 

class Quad : public ADTQuadTree{
private:
    Point topLeft;
    Point botRight;
    Node *n;
    vector<Node> nodesC;
    Quad *topLeftTree;
    Quad *topRightTree;
    Quad *botLeftTree;
    Quad *botRightTree;
    int pointCount = 0;

public:
    Quad(){
        topLeft = Point(0, 0);
        botRight = Point(0, 0);
        n = NULL; 
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
    }

    Quad(Point topL, Point botR){
        n = NULL;
        topLeftTree = NULL;
        topRightTree = NULL;
        botLeftTree = NULL;
        botRightTree = NULL;
        topLeft = topL;
        botRight = botR;
    }

    Node *search(Point);
    bool inBoundary(Point);
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    vector<int> list(); 
    int countRegion(Point p, int d);
    int AggregateRegion(Point p, int d);

};