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

bool Node::insert(Point _p, int _population) {

    bool inserted = false; // Bandera para indicar si se realizó una inserción
    if(!inBoundary(_p)){
        return inserted;
    }
    if (isLeaf()) {
        // Si es una hoja y hay datos, verifica si el punto ya existe
        if (n != NULL) {
        if (n->coords == _p) {
            n->population = _population;
            return false; // No se realiza una nueva inserción, solo se actualiza el valor existente
            }
        }

        // Si el tamaño mínimo de área se ha alcanzado, inserta el nuevo dato
         if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1) {
            n = new Data(_p, _population);
            inserted = true;
        } else {
            // Si aún es posible subdividir, realiza la subdivisión y luego inserta el dato en el cuadrante correspondiente
            subdivide();

            if ((topLeft.x + botRight.x) / 2 > _p.x) {
                if ((topLeft.y + botRight.y) / 2 > _p.y) {
                    inserted = topLeftTree->insert(_p, _population);
                } else {
                    inserted = botLeftTree->insert(_p, _population);
                }
            } else {
                if ((topLeft.y + botRight.y) / 2 > _p.y) {
                    inserted = topRightTree->insert(_p, _population);
                } else {
                    inserted = botRightTree->insert(_p, _population);
                }
            }
        }
    } else {
        // Si no es una hoja, realiza la inserción en el cuadrante correspondiente
        if ((topLeft.x + botRight.x) / 2 > _p.x) {
            if ((topLeft.y + botRight.y) / 2 > _p.y) {
                inserted = topLeftTree->insert(_p, _population);
            } else {
                inserted = botLeftTree->insert(_p, _population);
            }
        } else {
            if ((topLeft.y + botRight.y) / 2 > _p.y) {
                inserted = topRightTree->insert(_p, _population);
            } else {
                inserted = botRightTree->insert(_p, _population);
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
    // Si el nodo es una hoja, verifica cada dato si se encuentra dentro del área especificada
    if (isLeaf()) {
        if (n != NULL && isInsideRegion(n->coords, p, d))
            count++;
    } else {
        // Si no es una hoja, continúa el recorrido en los cuadrantes relevantes
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

int Node::AggregateRegion(Point p, int d) {
    int aggregate = 0;
    // Si el nodo es una hoja, verifica cada dato si se encuentra dentro del área especificada
    if (isLeaf()) {
        if (n != NULL && isInsideRegion(n->coords, p, d))
            aggregate += n->population;
    } else {
        // Si no es una hoja, continúa el recorrido en los cuadrantes relevantes
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
    // Recopila los datos de este nodo
    if (n != NULL){
        result.push_back(*n);
    }
    // Recorre los cuatro cuadrantes y recopila los datos de cada uno
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
			if (topLeftTree == NULL)
				return NULL;
			return topLeftTree->search(p);
		} else {
			if (botLeftTree == NULL)
				return NULL;
			return botLeftTree->search(p);
		}
	} else {
		if ((topLeft.y + botRight.y) / 2 > p.y) {
			if (topRightTree == NULL)
				return NULL;
			return topRightTree->search(p);
		} else {
			if (botRightTree == NULL)
				return NULL;
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
    // Obtiene los puntos medios de los límites actuales del nodo
    int midX = (topLeft.x + botRight.x) / 2;
    int midY = (topLeft.y + botRight.y) / 2;

    // Crea los cuatro nuevos nodos para la subdivisión
    topLeftTree = new Node(topLeft, Point(midX, midY));
    topRightTree = new Node(Point(midX, topLeft.y), Point(botRight.x, midY));
    botLeftTree = new Node(Point(topLeft.x, midY), Point(midX, botRight.y));
    botRightTree = new Node(Point(midX, midY), botRight);

    nodeCount += 4; // Incrementa el contador de nodos en 4 debido a la subdivisión
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

