#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#define MAX 5000

using namespace std;
using namespace std::chrono;

int partition_last(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int partition_random(vector<int>& arr, int low, int high) {
    int random_pivot = low + rand() % (high - low + 1);
    swap(arr[random_pivot], arr[high]);
    return partition_last(arr, low, high);
}

int partition_middle(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(arr[mid], arr[high]);
    return partition_last(arr, low, high);
}

void quickSort_last(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_last(arr, low, high);
        quickSort_last(arr, low, pi - 1);
        quickSort_last(arr, pi + 1, high);
    }
}

void quickSort_random(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_random(arr, low, high);
        quickSort_random(arr, low, pi - 1);
        quickSort_random(arr, pi + 1, high);
    }
}

void quickSort_middle(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition_middle(arr, low, high);
        quickSort_middle(arr, low, pi - 1);
        quickSort_middle(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0));
    ofstream archivo("datosQS-5000.csv");

    if(archivo.is_open()){
        archivo << "Tamanio,Mejor Caso,Peor Caso,Caso Promedio\n";

        for(int i=0; i<=MAX; i++){
            vector<int> mejorCaso(i), peorCaso(i), casoPromedio(i);

            for(int j=0; j<i; j++) {
                mejorCaso[j] = j + 1;
                peorCaso[j] = j + 1;
                casoPromedio[j] = rand() % 100;
            }

            auto inicioMejor = high_resolution_clock::now();
            quickSort_middle(mejorCaso, 0, i - 1);
            auto finMejor = high_resolution_clock::now();
            chrono::duration<double> duracionMejor = finMejor - inicioMejor;

            auto inicioPeor = high_resolution_clock::now();
            quickSort_last(peorCaso, 0, i - 1);
            auto finPeor = high_resolution_clock::now();
            chrono::duration<double> duracionPeor = finPeor - inicioPeor;

            auto inicioPromedio = high_resolution_clock::now();
            quickSort_random(casoPromedio, 0, i - 1);
            auto finPromedio = high_resolution_clock::now();
            chrono::duration<double> duracionPromedio = finPromedio - inicioPromedio;

            archivo<<i<<","
                <<fixed<<setprecision(10)<<duracionMejor.count()<<","
                <<fixed<<setprecision(10)<<duracionPeor.count()<<","
                <<fixed<<setprecision(10)<<duracionPromedio.count()<<"\n";
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo" << endl;
    }
    return 0;
}
