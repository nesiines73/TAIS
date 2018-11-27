#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

bool mayor(int a, int b) {
    return a > b;
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    
    if (!std::cin) return false;
    
    int sol = 0;
    PriorityQueue<int, std::greater<int>> rivales, defensa;
    
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        rivales.push(temp);
    }
    
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        defensa.push(temp);
    }
    
    while (!rivales.empty()) {
        int enemigosAtacando = rivales.top(), soldadosDefendiendo = defensa.top();
        if (enemigosAtacando > soldadosDefendiendo)
            rivales.pop();
        else {
            ++sol;
            rivales.pop();
            defensa.pop();
        }
    }

    std::cout << sol << "\n";
    
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
