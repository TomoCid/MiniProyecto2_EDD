#include "QuadThree.h"

using namespace std;

void Quad::insert(Point p, int data)
{
    Node* node = new Node(p, data);  // Create a new node with the given point and data
    
    if (!inBoundary(p))
        return;
 
    if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1) {
        if (n == NULL)
            n = node;
        return;
    }
 
    if ((topLeft.x + botRight.x) / 2 >= p.x) {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(p, data);  // Recursively insert into the top left subtree
        }
        else {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                          (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                          botRight.y));
            botLeftTree->insert(p, data);  // Recursively insert into the bottom left subtree
        }
    }
    else {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          topLeft.y),
                    Point(botRight.x,
                          (topLeft.y + botRight.y) / 2));
            topRightTree->insert(p, data);  // Recursively insert into the top right subtree
        }
        else {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(p, data);  // Recursively insert into the bottom right subtree
        }
    }
}

 
Node* Quad::search(Point p)
{
    if (!inBoundary(p))
        return NULL;
 
    if (n != NULL)
        return n;
 
    if ((topLeft.x + botRight.x) / 2 >= p.x) {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }
 
        else {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else {
        if ((topLeft.y + botRight.y) / 2 >= p.y) {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }
 
        else {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
}
 
bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x && p.x <= botRight.x
            && p.y >= topLeft.y && p.y <= botRight.y);
}

vector<int> Quad::list(){

}

int Quad::totalPoints(){}

int Quad::totalNodes(){}

int Quad::countRegion(Point p, int d){}

int Quad::AggregateRegion(Point p, int d){
    int count = 0;

    // Si estamos en el último nivel, revisamos si los datos que almacena cumplen con estar dentro de la distancia establecida
    if (isLeaf()) {
        // Se considera la "distancia total" entre una ciudad y p como el número de rectángulos (distance) multiplicado por el tamaño mínimo definido
        // para el ancho o alto (ancho/2)
        if (!data.empty() && abs(data[0].position.x - p.x) <= distance * MIN_WIDTH_SIZE && abs(data[0].position.y - p.y) <= distance * MIN_WIDTH_SIZE / 2) {
            // Sumamos las poblaciones guardadas en el vector
            for (int i = 0; i < data.size(); i++) {
                count += data[i].population;
            }
        }
    }
    else {
        if (topLeftNode != NULL) {
            count += topLeftNode->aggregateRegion(p, distance);
        }
        if (topRightNode != NULL) {
            count += topRightNode->aggregateRegion(p, distance);
        }
        if (botLeftNode != NULL) {
            count += botLeftNode->aggregateRegion(p, distance);
        }
        if (botRightNode != NULL) {
            count += botLeftNode->aggregateRegion(p, distance);
        }
    }

    return count;
}