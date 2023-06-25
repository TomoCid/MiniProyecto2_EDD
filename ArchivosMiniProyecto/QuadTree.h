#ifndef _QUADTREE
#define _QUADTREE

#include "Node.h"

using namespace std;

class QuadTree{
    private:
        Node* root;
        int numPoints;
        
    public:
        QuadTree(int size);

        void insert(Point p, int population, string cityname, string country);
        int totalPoints();
        int totalNodes();
        vector<Data> list();
        int countRegion(Point p, int d);
        long long AggregateRegion(Point p, int d);
};

#endif