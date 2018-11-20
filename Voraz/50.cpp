#include <iostream>
#include <vector>
#include <fstream>

bool resuelveCaso() {
    int numAgujeros, longParche, agujero1, agujero2, contParches = 1, contLongitud = 0;
    std::cin >> numAgujeros >> longParche;
    
    if (!std::cin) return false;
    
    std::vector<int> localizacion, sol;
    
    for (int i = 0; i < numAgujeros; ++i) {
        std::cin >> agujero1;
        localizacion.push_back(agujero1);
    }
    
    for (int i = 0; i < numAgujeros - 1; ++i) {
        agujero1 = localizacion[i];
        agujero2 = localizacion[i + 1];
        sol.push_back(agujero2 - agujero1);
    }
    
    for (int i = 0; i < sol.size(); ++i) {
        if (contLongitud + sol[i] <= longParche)
            contLongitud += sol[i];
        else {
            contLongitud = 0;
            ++contParches;
        }
    }
    
    std::cout << contParches << "\n";
    
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
