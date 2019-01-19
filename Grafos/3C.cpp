#include <iostream>
#include <fstream>
#include "Grafo.h"

bool dfs(Grafo const& G, int v, std::vector<int> &marked, bool const& ponGuardia, int &conGuardia, int &sinGuardia) {
   
    std::vector<int> ady = G.ady(v);
    
    bool posible = true;
    
    for (int i = 0; i < ady.size() && posible; ++i) {
        if (marked[ady.at(i)] == 0) {
            if (ponGuardia) {
                marked[ady.at(i)] = 2;
                ++sinGuardia;
            }
            else {
                marked[ady.at(i)] = 1;
                ++conGuardia;
            }
            
            posible = dfs(G, ady.at(i), marked, !ponGuardia, conGuardia, sinGuardia);
        }
        else {
            if (marked[v] == marked[ady.at(i)])
                posible = false;
        }
    }
    
    return posible;
}

int resolver(Grafo const& G) {
    
    std::vector<int> marcas(G.V(), 0);
    bool continua = true;
    int guardias = 0;
    
    for (int i = 1; i < G.V() && continua; ++i) {
        if (!marcas[i]) {
            int conGuardia = 1, sinGuardia = 0;
            marcas[i] = 1;
            continua = dfs(G, i, marcas, true, conGuardia, sinGuardia);
            guardias += std::min(conGuardia, sinGuardia);
        }
    }
    
    if (!continua) return -1;
    
    return guardias;
}

bool resuelveCaso() {
    int cruces, calles;
    std::cin >> cruces >> calles;
    
    if (!std::cin) return false;
    
    Grafo g(cruces + 1);
    
    for (int i = 1; i <= calles; ++i) {
        int v, w;
        std::cin >> v >> w;
        g.ponArista(v, w);
    }
    
    int sol = resolver(g);
    
    if (sol == -1) std::cout << "IMPOSIBLE\n";
    else std::cout << sol << "\n";
    
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
