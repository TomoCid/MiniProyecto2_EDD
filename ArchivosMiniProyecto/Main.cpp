#include "QuadTree.h"
#include <chrono>
#include <sstream>
#include <fstream>
#include <time.h>

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
		int element = 0;

		Data dataAux;
		while (getline(aux, field, ';')) { 
            int commaPos = field.find(',');
			if (commaPos != string::npos) {
				field[commaPos] = '.';
			}
			if(element==0){
				dataAux.country = field;
			} else if (element==1){
				dataAux.cityname = field;
			} else if (element == 4) { 
				dataAux.data = stoi(field);
			} else if (element == 5) {
				dataAux.coords.x = int((stod(field) + 90.0) * pow(10, 4));
			} else if (element == 6) {
				dataAux.coords.y = int((stod(field) + 180.0) * pow(10, 4));
			}
			element++;
		}
		dataBase.push_back(dataAux);
	}

	return dataBase;
}

int main(){
	srand(time(NULL));

    int numOps = 3173647;
    int tableSize = 360 * pow(10,4); //Coordenada más lejana
    int numTest = 20;
	int zone = 3600000;
    vector<Data> dataBase = File(numOps);
    QuadTree test(tableSize);

    cout<<"Info Test: " << tableSize << " tamaño tabla / " << numOps << " Nro. operaciones" << endl;
    cout << "Área de búsqueda: " << zone << " x " << zone << endl;

	for (int i = 0; i < numOps; i++) {  
        test.insert(dataBase[i].coords, dataBase[i].data, dataBase[i].cityname, dataBase[i].country);
    }
	cout<<"----------ÁREA EXPERIMENTAL----------"<<endl;
    chrono::high_resolution_clock::time_point inicio_1, final_1;
    double tiempo_final = 0;
    for (int i = 0; i < numTest; i++) {
        inicio_1 = chrono::high_resolution_clock::now();
        for(int i = 0; i<1; i++){  
            test.AggregateRegion(Point((90 + (rand() % 90)) * (pow(10,4)), (180 + (rand() % 180)) * (pow(10,4))), zone);
			//test.countRegion(Point((90 + (rand() % 90)) * (pow(10,4)), (180 + (rand() % 180)) * (pow(10,4))), zone);
        }
		final_1 = chrono::high_resolution_clock::now();
        auto qt_time_1 = chrono::duration_cast<chrono::microseconds>(final_1 - inicio_1).count();
        tiempo_final += qt_time_1;
	}
    double tiempo_promedio = tiempo_final / numTest;
    cout << "Tiempo promedio de ejecución: " << tiempo_promedio << " us" << endl;
    
	/*
	cout << test.totalNodes() << endl;
    cout << test.totalPoints() << endl;
	
    vector<Data> dataList = test.list();
    for (const auto& data : dataList) {
		cout << "Coordenadas geograficas: (" << data.geoCoords.geoX << ", " << data.geoCoords.geoY << ")" << endl;
    	cout << "Coordenadas ingresadas: (" << data.coords.x << ", " << data.coords.y << ")" << endl;
    	cout << "Población: " << data.data << endl;
		cout << "Nombre ciudad: " << data.cityname << endl;
		cout << "Nombre pais: " << data.country << endl;
    	cout << endl;
    }
	*/

    return 0;
}