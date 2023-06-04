#include "QuadThree.h"
int main() {
  Quad plane2D(Point(0, 0), Point(8, 8));


  plane2D.insert(Point(0, 0), 5);
  plane2D.insert(Point(0, 1), 4);
  plane2D.insert(Point(1, 0), 2);
  plane2D.insert(Point(1, 1), 2);
  plane2D.insert(Point(2, 1), 1);
  plane2D.insert(Point(5, 1), 3);
  plane2D.insert(Point(6, 2), 10);
  plane2D.insert(Point(7, 7), 8);
  
  cout << "Contenido en la coordenada (5,1): ";
  Node * p = plane2D.search(Point(5, 1));
  if(p != NULL) cout << p->data << endl;
  else cout << "No existe el punto." << endl;
  // Contenido en la coordenada (5,1): 3

  cout << "Contenido en la coordenada (1,5): ";
  p = plane2D.search(Point(1, 5));
  if(p != NULL) cout << p->data << endl;
  else cout << "No existe el punto." << endl;
  // Contenido en la coordenada (1,5): No existe el punto.
  
  return 0;
}