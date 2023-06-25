#include "QuadTree.h"
#include <chrono>
#include <sstream>
#include <fstream>


using namespace std;

vector<Data> File(int numDatas) {
	ifstream inputFile("cities.csv");
	vector<Data> dataBase;

	if (!inputFile.is_open()) {
		cout << "No se ha abierto el archivo correctamente." << endl;
		return dataBase;
	} else {
        cout << "El archivo se ha abierto con éxito." << endl;
    }

	string line;
	getline(inputFile, line); 
	for (int i = 0; i < numDatas; i++) { 
		getline(inputFile, line);

		istringstream aux(line); 
		string field;
		int currentField = 0;

		Data dataAux;
		while (getline(aux, field, ';')) { 
            int commaPos = field.find(',');
			if (commaPos != string::npos) {
				field[commaPos] = '.';
			}
			if (currentField == 4) { 
				dataAux.data = stoi(field);
			} else if (currentField == 5) {
				dataAux.originalCoords.originalX = stod(field);
				dataAux.coords.x = int((stod(field) + 90.0) * pow(10, 4));
			} else if (currentField == 6) {
				dataAux.originalCoords.originalY = stod(field);
				dataAux.coords.y = int((stod(field) + 180.0) * pow(10, 4));
			}
			currentField++;
		}
		dataBase.push_back(dataAux);
	}

	return dataBase;
}

int main(){
    int numOps = 10;
    int tableSize = 1000000000;
    int numTest = 1;
    vector<Data> dataBase = File(numOps);
    QuadTree test(tableSize);

    cout<<"Info Test: " << tableSize << " tamaño tabla / " << numOps << " Nro. operaciones" << endl;
    
    chrono::high_resolution_clock::time_point inicio_1, final_1;
    double tiempo_final = 0;
    for (int i = 0; i < numTest; i++) {
        inicio_1 = chrono::high_resolution_clock::now();
        for(int i = 0; i<numOps; i++){  
            test.insert(dataBase[i].coords, dataBase[i].data);
        }
		final_1 = chrono::high_resolution_clock::now();
        auto qt_time_1 = chrono::duration_cast<chrono::microseconds>(final_1 - inicio_1).count();
        tiempo_final += qt_time_1;
	}
    double tiempo_promedio = tiempo_final / numTest;
    cout << "Tiempo promedio de inserción en MapB: " << tiempo_promedio << " us" << endl;

    cout << test.totalNodes() << endl;
    cout << test.totalPoints() << endl;

    vector<Data> dataList = test.list();
    for (const auto& data : dataList) {
	cout << "Coordenadas originales: (" << data.originalCoords.originalX << ", " << data.originalCoords.originalY << ")" << endl;
    cout << "Coordenadas transformadas: (" << data.coords.x << ", " << data.coords.y << ")" << endl;
    cout << "Población: " << data.data << endl;
    cout << endl;
    }
    return 0;
}