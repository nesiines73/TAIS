#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

enum color{
    naranja,
    azul,
    sinColor
};

bool esAzulYBipartito(const Grafo &grafo, const int &v, std::vector<color>& coloreado);

bool esNaranjaYBipartito(const Grafo &grafo, const int &v, std::vector<color>& coloreado){
    coloreado[v] = naranja;
    for (int w : grafo.ady(v)){
        if (coloreado[w] != azul){
            if (coloreado[w] == naranja || !esAzulYBipartito(grafo, w,coloreado))
                return false;
        }
    }
    return true;
}

bool esAzulYBipartito(const Grafo &grafo, const int &v, std::vector<color>& coloreado){
    coloreado[v] = azul;
    for (int w : grafo.ady(v)){
        if (coloreado[w] != naranja){
            if (coloreado[w] == azul || !esNaranjaYBipartito(grafo, w, coloreado))
                return false;
        }
        
    }
    return true;
}

bool esBipartito(const Grafo &grafo){
    
    std::vector<color> coloreado(grafo.V(), sinColor);
    bool bipartito = true;
    
    for (int i = 0; i < grafo.V() && bipartito; i++){
        if(coloreado[i] == sinColor)
            bipartito = esAzulYBipartito(grafo, i, coloreado);
    }
    
    return bipartito;
}

bool resuelveCaso(){
    int V, E, v, w;
    std::cin >> V;
    
    if (!std::cin) return false;
    
    std::cin >> E;
    Grafo grafo(V);
    
    for (int i = 0; i < E; ++i) {
        std::cin >> v >> w;
        grafo.ponArista(v, w);
    }
   
    if (esBipartito(grafo))
        std::cout << "SI\n";
    else
        std::cout << "NO\n";
    
    return true;
}

int main(){
    
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());
    
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    
    return 0;
}
