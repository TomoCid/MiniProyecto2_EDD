#ifndef _NODE
#define _NODE

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Point{
    int x;
    int y;
    double originalX;
    double originalY;
    Point(int _x, int _y){
        x=_x;
        y=_y;
    }

    Point(){
        x=0;
        y=0;
        originalX = 0.0;
        originalY = 0.0;
    }

    bool operator==(const Point& other) const {
        return (x == other.x) && (y == other.y);
    }
};

struct Data{
    Point originalCoords;
    Point coords;
    int data;
    string cityname;
    string country;

    Data(Point _coords, int _data, string _cityname, string _country){
        coords = _coords;
        data = _data;
        cityname = _cityname;
        country = _country;
        originalCoords.originalX = (double(coords.x) / pow(10, 4))- 90;
        originalCoords.originalY = (double(coords.y) / pow(10, 4))- 180;
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
        bool insert(Point _p, int _data, string cityname, string country);
        int numNodes();
        vector<Data> list();
        int countRegion(Point p, int d);
        long long AggregateRegion(Point p, int d);

        //Metodos auxiliares
        bool isLeaf();
        bool inBoundary(Point _p);
        void subdivide();
        bool isInsideRegion(Point nodeCoords, Point p, int d);
};

#endif
