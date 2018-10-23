#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "GrafoDirigido.h"

class Arborescencia{
public:
    Arborescencia(const GrafoDirigido &grafo){
        int nodosVisitados = 0,
        v = grafo.V();
        raiz = -1;
        bool salir = false;
        GrafoDirigido inverso = grafo.inverso();
        marcados = std::vector<bool>(v, false);
        
        for (int i = 0; i < v && !salir; i++){
            if (inverso.ady(i).size() == 0){
                if (raiz == -1){
                    nodosVisitados = 1;
                    if (dfs(grafo, i, nodosVisitados) && nodosVisitados == v){
                        raiz = i;
                        salir = true;
                    }
                }
                else
                    salir = true;
            }
        }
    }
    
    int getRaiz(){
        return raiz;
    }
    
private:
    
    int raiz;
    std::vector<bool> marcados;
    
    bool dfs(GrafoDirigido const& G, size_t v,int& nodos_visitados) {
        marcados[v] = true;
        
        for (size_t w : G.ady(v)) {
            if (!marcados[w]) {
                nodos_visitados++;
                if (!dfs(G, w, nodos_visitados))
                    return false;
            }
            else
                return false;
        }
        return true;
    }
};


bool resuelveCaso(){
    
    int V, A, v, w;
    
    std::cin >> V >> A;
    
    if (!std::cin) return false;
    
    GrafoDirigido grafo(V);
    
    for (int i = 0; i < A; ++i){
        std::cin >> v >> w;
        grafo.ponArista(v, w);
    }
    
    Arborescencia arborescencia(grafo);
    
    if (arborescencia.getRaiz() >= 0)
        std::cout << "SI " << arborescencia.getRaiz() << "\n";
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
