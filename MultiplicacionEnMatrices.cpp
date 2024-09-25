#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>  
#include <ctime>    
#include <fstream>

using namespace std;
using namespace std::chrono;

void multiplicarMatricesPorBloques(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int N, int tam_bloque) {
    for (int i_bloque = 0; i_bloque < N; i_bloque += tam_bloque) {
        for (int j_bloque = 0; j_bloque < N; j_bloque += tam_bloque) {
            for (int k_bloque = 0; k_bloque < N; k_bloque += tam_bloque) {
                // Multiplicacion de submatrices
                for (int i = i_bloque; i < min(i_bloque + tam_bloque, N); i++) {
                    for (int j = j_bloque; j < min(j_bloque + tam_bloque, N); j++) {
                        for (int k = k_bloque; k < min(k_bloque + tam_bloque, N); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

void inicializarMatrizAleatoria(vector<vector<int>>& matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = rand() % 100;  
        }
    }
}

int main() {
    srand(time(0));  

    ofstream archivo("comparacion_tiempos.txt");

    vector<int> tamanios = {100, 150, 200, 300, 450, 800};  // Puedes ajustar estos valores
    int tam_bloque = 50;  // Tamaño del bloque a usar

    for (int size : tamanios) {
        int N = size;

        // Crear matrices A, B y C para ambas versiones
        vector<vector<int>> A(N, vector<int>(N));
        vector<vector<int>> B(N, vector<int>(N));
        vector<vector<int>> C_clasico(N, vector<int>(N, 0));
        vector<vector<int>> C_bloques(N, vector<int>(N, 0));


        inicializarMatrizAleatoria(A, N, N);
        inicializarMatrizAleatoria(B, N, N);

        // Multiplicación de matrices clásica
        auto start_clasico = high_resolution_clock::now();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++) {
                    C_clasico[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        auto stop_clasico = high_resolution_clock::now();
        auto duration_clasico = duration_cast<milliseconds>(stop_clasico - start_clasico);

        // Multiplicación de matrices por bloques
        auto start_bloques = high_resolution_clock::now();
        multiplicarMatricesPorBloques(A, B, C_bloques, N, tam_bloque);
        auto stop_bloques = high_resolution_clock::now();
        auto duration_bloques = duration_cast<milliseconds>(stop_bloques - start_bloques);

        archivo << size << " " << duration_clasico.count() << " " << duration_bloques.count() << endl;

        cout << "Tamaño: " << N << "x" << N << " - Clásico: " << duration_clasico.count()
             << " ms, Bloques: " << duration_bloques.count() << " ms" << endl;
    }

    archivo.close();  // Cerrar archivo
    return 0;
}
     
