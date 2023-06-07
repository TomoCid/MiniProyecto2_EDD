#include "QuadTree.h"
#include <vector>

int main() {
  Quad plane2D(Point(0, 0), Point(4, 4));

  plane2D.insert(Point(0, 0), 5);
  plane2D.insert(Point(0, 1), 4);
  plane2D.insert(Point(1, 0), 2);
  plane2D.insert(Point(1, 1), 2);
  plane2D.insert(Point(3, 3), 2);

  cout<<"Total de nodos: "<<plane2D.totalNodes();

  return 0;
}