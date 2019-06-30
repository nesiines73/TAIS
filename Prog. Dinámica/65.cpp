//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <string>
#include "Matriz.h"

/*
        |0 si i = j
G[i][j] |coste si hay arista de i a j
        |INF si no hay arista de i a j
 
 Coste en tiempo O(n^3)
 Coste en espacio adicional O(1 + HashMap)
 */

const int INF = std::numeric_limits<int>::max();

//Floyd
void Floyd (Matriz<int> const &G, Matriz<int> &C, Matriz<int> &camino) {
    int n = G.numfils() - 1;
    C = G;
    camino = Matriz<int>(n + 1, n + 1, 0);
    
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                unsigned long temp = C[i][k] + C[k][j];
                if(temp < C[i][j]) {
                    C[i][j] = temp;
                    camino[i][j] = k;
                }
            }
        }
    }
}

bool resuelveCaso() {
    int V, E;
    std::cin >> V >> E;
    if(!std::cin) return false;
    
    std::unordered_map<std::string, int> mapa;
    
    Matriz<int> grafo(V+1,V+1,INF);
    
    for(int u = 1; u <= V; ++u)
        grafo[u][u] = 0;
    
    int id = 1;
    
    for (int i = 0; i < E; ++i) {
        std::string p1, p2;
        
        std::cin >> p1 >> p2;
        if (mapa[p1] == 0) {
            mapa[p1] = id;
            ++id;
        }
        if (mapa[p2] == 0){
            mapa[p2] = id;
            ++id;
        }
        
        grafo[mapa[p1]][mapa[p2]] = 1;
        grafo[mapa[p2]][mapa[p1]] = 1;
    }
    
    Matriz<int> C(0,0), camino(0,0);
    Floyd(grafo, C, camino);
    
    int max = 0;
    
    for (int i = 1; i <= V; ++i){
        for (int j = 1; j <= V; ++j)
            max = std::max(max, C[i][j]);
    }
    
    if (max == INF) std::cout << "DESCONECTADA\n";
    else std::cout << max << "\n";
    
    
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
