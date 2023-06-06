#ifndef _ADTQUADTHREE
#define _ADTQUADTHREE
#include "Structs.h"
#include <vector>
using namespace std;
class ADTAQueadThree
{
public: 
    virtual int totalPoints() = 0;
    virtual int totalNodes() = 0;
    virtual void insert(Point p, int data) = 0;
    virtual vector<int> list()=0;  //"AQUI SE DEBE DECIDIR CONTENEDOR"  
    virtual int countRegion(Point p, int d)=0;
    virtual int AggregateRegion(Point p, int d)=0;

private: 

};
#endif 