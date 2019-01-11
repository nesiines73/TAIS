#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"


void resuelve(Matriz<int> const& matOriginal, int &colIni, int &sumaTotal, const int &N) {
    Matriz<int> matriz(N+1, N+2, 0);
    
    for (int f = 1; f <= N; ++f) {
        for (int c = 1; c <= N; ++c) {
            matriz[f][c] = std::max(matOriginal[f][c] + matriz[f-1][c-1], std::max(matOriginal[f][c] + matriz[f-1][c], matOriginal[f][c] + matriz[f-1][c+1]));
        }
    }
    
    sumaTotal = matriz[N][0];
    colIni = 0;
    
    for (int i = 1; i <= N; ++i) {
        if (sumaTotal < matriz[N][i]) {
            sumaTotal = matriz[N][i];
            colIni = i;
        }
    }
    
}


bool resuelveCaso() {
    int N;
    std::cin >> N;
    
    if (!std::cin) return false;
    
    Matriz<int> mat(N+1, N+1);
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
