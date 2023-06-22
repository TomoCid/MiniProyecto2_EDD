#include "QuadTree.h"

using namespace std;

int main(){
    QuadTree testeo(8);
    cout<<testeo.totalNodes()<<" , "<<testeo.totalPoints()<<endl;
    testeo.insert(Point(0,0),1);
    testeo.insert(Point(0,1),4);
    testeo.insert(Point(1,0),2);
    testeo.insert(Point(1,1),2);
    testeo.insert(Point(2,1),1);
    testeo.insert(Point(5,1),3);
    testeo.insert(Point(6,2),10);
    testeo.insert(Point(7,7),8);
    cout<<testeo.totalNodes()<<" , "<<testeo.totalPoints()<<endl;
    cout<<testeo.AggregateRegion(Point(4, 2), 2)<<endl;
    cout<<testeo.countRegion(Point(4, 2), 2)<<endl;

    QuadTree testeo_2(8);
    testeo_2.insert(Point(0,0),1);
    cout<<testeo_2.totalNodes()<<" , "<<testeo_2.totalPoints()<<endl;

    return 0;
}