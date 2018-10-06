#include <fstream>
#include <iostream>
#include <vector>

#include "Mediana.h"


//Coste O(nlogn). Logaritmica al insertar, n al recorrer.
bool resuelveCaso(){
    unsigned int n;
    std::cin >> n;
    
    if (n == 0)  return false;
    
    ColaMedianas<int> c;
    
    for (int i = 0; i < n; ++i) {
        int aux;
        std::cin >> aux;
        if (aux >= 0) {
            c.push(aux);
            int m = c.mediana();
            std::cout << m;
        }
        if (i != n-1)
            std::cout << " ";
    }
    std::cout << "\n";
    
    return true;
}

int main() {// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while(resuelveCaso());
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
