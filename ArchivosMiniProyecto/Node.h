#ifndef _NODE
#define _NODE

#include <iostream>
#include <vector>

using namespace std;

struct Point{
    int x;
    int y;
    Point(int _x, int _y){
        x=_x;
        y=_y;
    }
    Point(){
        x=0;
        y=0;
    }
    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

struct Data{
    Point coords;
    int data;
    Data(Point _coords, int _data){
        coords = _coords;
        data = _data;
    }
    Data(){
        data = 0;
    }
};

class Node{
    private:
        Point topLeft;
        Point botRight;

        Data *n;

        Node *topLeftTree;//Primer cuadrante
        Node *topRightTree;//Segundo cuadrante
        Node *botLeftTree;//Tercer cuadrante
        Node *botRightTree;//Cuarto cuadrante

        static int nodeCount;

    public:
        //Constructor
        Node(Point _topLeft, Point _topRight);
        Node();

        //Metodos principales
        bool insert(Point _p, int _data);
        Data *search(Point _p);
        int numNodes();
        vector<Data> list();
        int countRegion(Point p, int d);
        int AggregateRegion(Point p, int d);

        //Metodos auxiliares
        bool isLeaf();
        bool inBoundary(Point _p);
        void subdivide();
        bool isInsideRegion(Point nodeCoords, Point p, int d);

        //Solución temporal al contador de nodos (O(log n))
        int countNodes();
};

#endif
