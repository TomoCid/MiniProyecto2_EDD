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
    int population;
    Data(Point _coords, int _population){
        coords = _coords;
        population = _population;
    }
    Data(){
        population = 0;
    }
};

class Node{
    private:
        Point topLeft;
        Point botRight;

        Data *n;
        vector<Data> datas;

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
        bool insert(Point _p, int _population);
        Data *search(Point _p);
        int numNodes();
        vector<Data> list();
        int countRegion(Point p, int d); //En testeo, de momento solo retorna 0
        int AggregateRegion(Point p, int d);

        //Metodos auxiliares
        bool isLeaf();
        bool inBoundary(Point _p);
        void subdivide();
        bool isInsideRegion(Point nodeCoords, Point p, int d);
};

#endif
