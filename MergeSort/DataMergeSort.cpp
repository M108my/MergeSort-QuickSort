#include <iostream>
#include <chrono>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iomanip>

#define MAX 50

using namespace std;
using namespace std::chrono;

void merge(vector<int>& arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}


int main() {
    ofstream archivo("datosMS-50.csv");

    if(archivo.is_open()){
        archivo << "Tamanio,Mejor Caso,Peor Caso,Caso Promedio\n";

        for(int i=0; i<=MAX; i++){
            vector<int> mejorCaso(i), peorCaso(i), casoPromedio(i);

            for (int j = 0; j < i; j++) {
                mejorCaso[j] = j+1; //Ordenado ascendente
                peorCaso[j] = i-j; //Ordenado descendente
                casoPromedio[j] = rand() % 100; //Valores aleatorios
            }

            auto inicioMejor = high_resolution_clock::now();
            mergeSort(mejorCaso, 0, i - 1);
            auto finMejor = high_resolution_clock::now();
            chrono::duration<double> duracionMejor = finMejor - inicioMejor;

            auto inicioPeor = high_resolution_clock::now();
            mergeSort(peorCaso, 0, i - 1);
            auto finPeor = high_resolution_clock::now();
            chrono::duration<double> duracionPeor = finPeor - inicioPeor;

            auto inicioPromedio = high_resolution_clock::now();
            mergeSort(casoPromedio, 0, i - 1);
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
