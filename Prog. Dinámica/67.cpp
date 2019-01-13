#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "Matriz.h"

int come(const std::vector<int> &cubos, const int &n) {
    Matriz<int> matrizCubos(n + 1, n + 1, 0);
    int f;
    
    if (n == 1) return cubos[1];
    else if (n == 2) return std::max(cubos[1], cubos[2]);
    
    if (n % 2 == 0) {
        for (int i = 1; i < n; ++i)
            matrizCubos[i][i+1] = std::max(cubos[i], cubos[i+1]);
        f = 3;
    } else {
        for (int i = 1; i <= n; ++i)
            matrizCubos[i][i] = cubos[i];
        f = 2;
    }
    
    for (int d = f; d < n; d = d + 2) {
        for (int c = 1; c <= n - d; ++c) {
            int j = d + c, comoYo = 0, comoDevoradora = 0;
            if (cubos[j] > cubos[c + 1])
                comoYo = matrizCubos[c + 1][j - 1];
            else
                comoYo = matrizCubos[c + 2][j];
            
            if (cubos[c] > cubos[j - 1])
                comoDevoradora = matrizCubos[c + 1][j - 1];
            else
                comoDevoradora = matrizCubos[c][j - 2];
            matrizCubos[c][j] = std::max(cubos[c] + comoYo, cubos[j] + comoDevoradora);
        }
    }
    
    return matrizCubos[1][n];
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    
    if (n == 0) return false;
    
    std::vector<int> cubos(n + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        std::cin >> cubos[i];
    }
    
    std::cout << come(cubos, n) << "\n";
    
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
