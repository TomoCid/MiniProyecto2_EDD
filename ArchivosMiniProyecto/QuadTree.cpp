#include "QuadTree.h"
#include <vector>

using namespace std;

void Quad::insert(Point p, int data)
{
    Node *node = new Node(p, data);

    if (!inBoundary(p))
        return;

    if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1)
    {
        //Una vez encontramos la casilla, ingresamos el nodo y remplazamos si ya existe uno.
        n = node;
        return;
    }

    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
             //PROBANDOOOOOO
            if (topLeftTree == NULL)
                topLeftTree = new Quad(
                    Point(topLeft.x, topLeft.y),
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2));
            topLeftTree->insert(p, data); // Recursively insert into the top left subtree
        }
        else
        {
            if (botLeftTree == NULL)
                botLeftTree = new Quad(
                    Point(topLeft.x,
                          (topLeft.y + botRight.y) / 2),
                    Point((topLeft.x + botRight.x) / 2,
                          botRight.y));
            botLeftTree->insert(p, data); // Recursively insert into the bottom left subtree
        }
    }
    else
    {
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                topRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          topLeft.y),
                    Point(botRight.x,
                          (topLeft.y + botRight.y) / 2));
            topRightTree->insert(p, data); // Recursively insert into the top right subtree
        }
        else
        {
            if (botRightTree == NULL)
                botRightTree = new Quad(
                    Point((topLeft.x + botRight.x) / 2,
                          (topLeft.y + botRight.y) / 2),
                    Point(botRight.x, botRight.y));
            botRightTree->insert(p, data); // Recursively insert into the bottom right subtree
        }
    }
}

Node *Quad::search(Point p) // VER AL FINAL ES UN EXTRA
{
    if (!inBoundary(p))
        return NULL;

    if (n != NULL)
        return n;

    if ((topLeft.x + botRight.x) / 2 >= p.x)
    {
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topLeftTree == NULL)
                return NULL;
            return topLeftTree->search(p);
        }

        else
        {
            if (botLeftTree == NULL)
                return NULL;
            return botLeftTree->search(p);
        }
    }
    else
    {
        if ((topLeft.y + botRight.y) / 2 >= p.y)
        {
            if (topRightTree == NULL)
                return NULL;
            return topRightTree->search(p);
        }

        else
        {
            if (botRightTree == NULL)
                return NULL;
            return botRightTree->search(p);
        }
    }
}

bool Quad::inBoundary(Point p)
{
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

vector<int> Quad::list()
{
    vector<int> result;
 
    if (n != NULL)
        result.push_back(n->data);
 
    if (topLeftTree != NULL) {
        vector<int> topLeftList = topLeftTree->list();
        result.insert(result.end(), topLeftList.begin(), topLeftList.end());
    }
 
    if (topRightTree != NULL) {
        vector<int> topRightList = topRightTree->list();
        result.insert(result.end(), topRightList.begin(), topRightList.end());
    }
 
    if (botLeftTree != NULL) {
        vector<int> botLeftList = botLeftTree->list();
        result.insert(result.end(), botLeftList.begin(), botLeftList.end());
    }
 
    if (botRightTree != NULL) {
        vector<int> botRightList = botRightTree->list();
        result.insert(result.end(), botRightList.begin(), botRightList.end());
    }
 
    return result;
}

int Quad::totalPoints() {}


int Quad::totalNodes() {
    int count = 1;  

    if (topLeftTree != NULL)
        count += topLeftTree->totalNodes();

    if (topRightTree != NULL)
        count += topRightTree->totalNodes();

    if (botLeftTree != NULL)
        count += botLeftTree->totalNodes();

    if (botRightTree != NULL)
        count += botRightTree->totalNodes();

    return count;
}

int Quad::countRegion(Point p, int d) {}

int Quad::AggregateRegion(Point p, int d) {}