//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

/*
    porciones(i,j)= num máximo de veces que las gemelas pueden comer i trozos de la fruta j.
 
    Caso base
 
        porciones(i,j) = 0 si i > j || (pastel(i) != pastel(i+1) && pastel(i) == 0)
        porciones(i,j) = 1 si i == i+1 && (pastel(i) == pastel(i+1) && pastel(i) != 0)
 
    Recursion
        porciones(i,j) = max(porciones(i+2,j), porciones(i,j-2), porciones(i+1,j-1)) si pastel(i) != pastel(j) || pastel(i) == 0
        porciones(i,j) = porciones(i+1,j-1) + 1 si pastel(i) == pastel(j) && pastel(i) != 0
 
 Coste en tiempo  O(n^2)
 Coste en espacio O(n^2)
*/


int resuelve(const std::vector<int> &pastel, int N) {
    
    Matriz<int> porciones(N + 1, N + 1, 0);
    
    for (int d = 1; d <= N; ++d) { //O(n)
        if (pastel[d] == pastel[d+1] && pastel[d] != 0)
            porciones[d][d+1] = 1;
    }
    
    for (int d = 3; d <= N; d += 2) { //O(n^2)
        for(int i = 1; i <= N - d; ++i) {
            int j = i + d;
            if (pastel[i] == pastel[j] && pastel[i] != 0)
                porciones[i][j] = porciones[i+1][j-1] + 1;
            else
                porciones[i][j] = std::max(porciones[i + 2][j], std::max(porciones[i][j - 2], porciones[i+1][j-1]));
        }
    }
    
    return porciones[1][N];
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    
    if (!std::cin) return false;
    
    std::vector<int> pastel(n + 1, 0);
    
    for (int i = 1; i <= n; ++i)
        std::cin >> pastel[i];
    
    std::cout << resuelve(pastel, n) << "\n";
    
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
