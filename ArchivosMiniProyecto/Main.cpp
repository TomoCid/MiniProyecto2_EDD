#include "QuadTree.h"

using namespace std;

int main(){
    QuadTree qt(8);
    cout<<qt.totalNodes()<<" , "<<qt.totalPoints()<<endl;
    qt.insert(Point(0,0),1);
    qt.insert(Point(0,1),4);
    qt.insert(Point(1,0),2);
    qt.insert(Point(1,1),2);
    qt.insert(Point(2,1),1);
    qt.insert(Point(5,1),3);
    qt.insert(Point(6,2),10);
    qt.insert(Point(7,7),8);
    cout<<qt.totalNodes()<<" , "<<qt.totalPoints()<<endl;
    cout<<qt.AggregateRegion(Point(4, 2), 2)<<endl;
    cout<<qt.countRegion(Point(4, 2), 2)<<endl;
    
    //cout<<qt.totalNodes()<<" , "<<qt.totalPoints()<<endl;
    return 0;
}