//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

/*
 tablero(i,j) = Maximo valor posible hasta la fila i y la columna j del mismo.

 tablero(i,j) = max(tablero[i-1][j-1],tablero[i-1][j],tablero[i-1][j+1]) + tablero[i][j]
 
 Costes:
    O(N^2) en espacio.
    O(N^2 + N) en tiempo
 */

void resuelve(Matriz<int> &tablero, int &colIni, int &sumaTotal, const int &N) {
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j)
            tablero[i][j] = std::max(tablero[i-1][j-1], std::max(tablero[i-1][j],  tablero[i-1][j+1])) + tablero[i][j];
    }
    
    sumaTotal = tablero[N][0];
    colIni = 0;
    
    for (int i = 1; i <= N; ++i) {
        if (sumaTotal < tablero[N][i]) {
            sumaTotal = tablero[N][i];
            colIni = i;
        }
    }
    
}


bool resuelveCaso() {
    int N;
    std::cin >> N;
    
    if (!std::cin) return false;
    
    Matriz<int> mat(N+1, N+2, 0);
    for (int i = 1; i <= N; ++i) {
        for (int n = 1; n <= N; ++n)
            std::cin >> mat[i][n];
    }
    
    int sol = 0, max = 0;
    resuelve(mat, sol, max, N);
    
    std::cout << max << " " << sol << "\n";
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
