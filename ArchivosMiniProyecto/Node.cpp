#include "Node.h"

using namespace std;

Node::Node(Point topL, Point botR){
    topLeft = topL;
    botRight = botR;
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    n = NULL;
}

Node::Node(){
    topLeft = Point(0, 0);
    botRight = Point(0, 0);
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    n = NULL;
}

int Node::nodeCount = 1;

bool Node::insert(Point _p, int _data) {

    bool inserted = false;
    
    if(!inBoundary(_p)){
        return inserted;
    }

    if (isLeaf()) {
        if (n != NULL) {
            if (n->coords == _p) {
                n->data = _data;
                return false;
            }
        }

         if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1) {
            n = new Data(_p, _data);
            inserted = true;
        } else {
            subdivide();
            if ((topLeft.x + botRight.x) / 2 > _p.x) {
                if ((topLeft.y + botRight.y) / 2 > _p.y) {
                    inserted = topLeftTree->insert(_p, _data);
                } else {
                    inserted = botLeftTree->insert(_p, _data);
                }
            } else {
                if ((topLeft.y + botRight.y) / 2 > _p.y) {
                    inserted = topRightTree->insert(_p, _data);
                } else {
                    inserted = botRightTree->insert(_p, _data);
                }
            }
        }
    } else {
        if ((topLeft.x + botRight.x) / 2 > _p.x) {
            if ((topLeft.y + botRight.y) / 2 > _p.y) {
                inserted = topLeftTree->insert(_p, _data);
            } else {
                inserted = botLeftTree->insert(_p, _data);
            }
        } else {
            if ((topLeft.y + botRight.y) / 2 > _p.y) {
                inserted = topRightTree->insert(_p, _data);
            } else {
                inserted = botRightTree->insert(_p, _data);
            }
        }
    }

    return inserted;
}

int Node::numNodes(){
    return nodeCount;
}

int Node::countRegion(Point p, int d) {

    int count = 0;

    if (isLeaf()) {
        if (n != NULL && isInsideRegion(n->coords, p, d))
            count++;
    } else {
        if (topLeftTree != nullptr)
            count += topLeftTree->countRegion(p, d);
        if (topRightTree != nullptr)
            count += topRightTree->countRegion(p, d);
        if (botLeftTree != nullptr)
            count += botLeftTree->countRegion(p, d);
        if (botRightTree != nullptr)
            count += botRightTree->countRegion(p, d);
    }

    return count;
}

long long Node::AggregateRegion(Point p, int d) {
    long long aggregate = 0;

    if (isLeaf()) {
        if (n != NULL && isInsideRegion(n->coords, p, d))
            aggregate += n->data;
    } else {

        if (topLeftTree != nullptr)
            aggregate += topLeftTree->AggregateRegion(p, d);
        if (topRightTree != nullptr)
            aggregate += topRightTree->AggregateRegion(p, d);
        if (botLeftTree != nullptr)
            aggregate += botLeftTree->AggregateRegion(p, d);
        if (botRightTree != nullptr)
            aggregate += botRightTree->AggregateRegion(p, d);
    }
    return aggregate;
}

vector<Data> Node::list(){
    vector<Data> result;

    if (n != NULL) {
        result.push_back(*n);
    }

    if (topLeftTree != nullptr) {
        vector<Data> tlData = topLeftTree->list();
        result.insert(result.end(), tlData.begin(), tlData.end());
    }
    if (topRightTree != nullptr) {
        vector<Data> trData = topRightTree->list();
        result.insert(result.end(), trData.begin(), trData.end());
    }
    if (botLeftTree != nullptr) {
        vector<Data> blData = botLeftTree->list();
        result.insert(result.end(), blData.begin(), blData.end());
    }
    if (botRightTree != nullptr) {
        vector<Data> brData = botRightTree->list();
        result.insert(result.end(), brData.begin(), brData.end());
    }
    return result;
}

Data* Node::search(Point p) {

	if (!inBoundary(p)){
        return NULL;
    }
		
	if (n != NULL) {
        return n;
    }
		
	if ((topLeft.x + botRight.x) / 2 > p.x) {
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topLeftTree == NULL){
                return NULL;
            }
			return topLeftTree->search(p);
		} else {
			if (botLeftTree == NULL){
                return NULL;
            }
			return botLeftTree->search(p);
		}
	} else {
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topRightTree == NULL){
                return NULL;
            }
			return topRightTree->search(p);
		} else {
			if (botRightTree == NULL){
                return NULL;
            }
			return botRightTree->search(p);
		}
	}
}

//Metodos auxiliares
bool Node::isLeaf() {
    return (topLeftTree == NULL && topRightTree == NULL && botLeftTree == NULL && botRightTree == NULL);
}

bool Node::inBoundary(Point p) {
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

void Node::subdivide() {

    int midX = (topLeft.x + botRight.x) / 2;
    int midY = (topLeft.y + botRight.y) / 2;

    topLeftTree = new Node(topLeft, Point(midX, midY));
    topRightTree = new Node(Point(midX, topLeft.y), Point(botRight.x, midY));
    botLeftTree = new Node(Point(topLeft.x, midY), Point(midX, botRight.y));
    botRightTree = new Node(Point(midX, midY), botRight);

    nodeCount += 4;
}

bool Node::isInsideRegion(Point nodeCoords, Point p, int d) {

    int left = p.x - d;
    int right = p.x + d;
    int top = p.y + d;
    int bottom = p.y - d;

    if (nodeCoords.x >= left && nodeCoords.x <= right && nodeCoords.y >= bottom && nodeCoords.y <= top){
        return true;
    }
    return false;
}

