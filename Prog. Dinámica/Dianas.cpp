#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include "Matriz.h"

/*
    DIANA SIN OPTIMIZAR
    diana(i,j) = mínimo número de tiradas necesarias para conseguir la cantidad j con i sectores.
 
 Caso base:
    diana(i,0) = 0
    diana(0,j) = INF
 
 Caso recursivo:
    diana(i,j) = diana(i-1,j) si sectores[i] > j
    diana(i,j) = min(diana(i-1,j), diana(i,j-sectores[i]+1) si sectores[i] <= j
 
 
 COSTE:
    O(n*P) en tiempo y espacio, siendo n el numero de sectores y p la puntuación a obtener.
 
 */

const unsigned INF = 1e9;

bool resuelveCaso() {
    
    int cantidad, sectores;
    
    std::cin >> cantidad >> sectores;
    
    if (!std::cin) return false;
    
    std::vector<int> puntuaciones(sectores + 1);
    
    for (int i = 1; i <= sectores; ++i) {
        int tmp;
        std::cin >> tmp;
        puntuaciones[i] = tmp;
    }
    
    Matriz<int> diana(sectores + 1, cantidad + 1, INF);
    
   diana[0][0] = 0;
    
    for (int i = 1; i <= sectores; ++i) {
        diana[i][0] = 0;
        for (int j = 1; j <= cantidad; ++j) {
            if (puntuaciones[i] > j)
                diana[i][j] = diana[i-1][j];
            else
                diana[i][j] = std::min(diana[i-1][j], diana[i][j-puntuaciones[i]] + 1);
        }
    }
    
    if (diana[sectores][cantidad] >= INF) std::cout << "IMPOSIBOL";
    else {
        std::cout << diana[sectores][cantidad] << ":";
        
        int n = puntuaciones.size() - 1;
        std::vector<int> cuantas(n+1, 0);
        int i = n, j = cantidad;
        while(j > 0) {
            if(puntuaciones[i] <= j && diana[i][j] != diana[i-1][j]) {
                ++cuantas[i];
                j = j - puntuaciones[i];
                
            }else
                --i;
        }
        
        /*int i = sectores, j = cantidad;
        std::vector<int> cuantas(sectores+1,0);
        while(j > 0) {
            if(puntuaciones[i] <= j && diana[i][j] != diana[i-1][j]) {
                ++cuantas[i];
                j = j - puntuaciones[i];
            } else
                --i;
        }*/
        
        std::sort(puntuaciones.begin(), puntuaciones.end());
        
        for (int i = sectores; i > 0; i--) {
            for (int j = cuantas[i]; j > 0; j--) {
                std::cout << " " << puntuaciones[i];
            }
        }
    }
    
    std::cout << "\n";
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
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
