#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>  
#include <ctime>    
using namespace std;
using namespace std::chrono;

const int MAX = 1000;

// Función para inicializar las matrices y vectores
void inicializarMatrizYVectores(double A[MAX][MAX], double x[MAX], double y[MAX]) {
    srand(time(0));  
    for (int i = 0; i < MAX; i++) {
        x[i] = rand() % 100;  
        y[i] = 0;  
        for (int j = 0; j < MAX; j++) {
            A[i][j] = rand() % 100;  
        }
    }
}

// Primer par de bucles: acceso por filas
void primerBucle(double A[MAX][MAX], double x[MAX], double y[MAX]) {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

// Segundo par de bucles: acceso por columnas
void segundoBucle(double A[MAX][MAX], double x[MAX], double y[MAX]) {
    for (int j = 0; j < MAX; j++) {
        for (int i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
}

int main() {
    double A[MAX][MAX], x[MAX], y[MAX];

    inicializarMatrizYVectores(A, x, y);  // Inicializar matriz y vectores

    // Evaluar el primer par de bucles
    auto start1 = high_resolution_clock::now();
    primerBucle(A, x, y);
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);
    cout << "Tiempo de ejecución del primer par de bucles: " << duration1.count() << " ms" << endl;

    // Reiniciar el vector y para la segunda evaluación
    fill(begin(y), end(y), 0);  // Reiniciar el vector y a 0

    // Evaluar el segundo par de bucles
    auto start2 = high_resolution_clock::now();
    segundoBucle(A, x, y);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    cout << "Tiempo de ejecución del segundo par de bucles: " << duration2.count() << " ms" << endl;

    return 0;
}
