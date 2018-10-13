#include <fstream>
#include <iostream>
#include <vector>

#include "Grafo.h"

class MaxCompCon {
public:
    MaxCompCon(const Grafo &G) : marked(G.V(), false), _maximo(0) {
        for (int v = 0; v < G.V(); ++v) {
            if (!marked[v]) {
                int tam = 0;
                busqProfundidad(G, v, tam);
                _maximo = std::max(_maximo, tam);
            }
        }
    }
    
    int maximo() const {
        return _maximo;
    }
    
private:
    std::vector<bool> marked;
    int _maximo;
    
    void busqProfundidad(const Grafo &G, const int &v, int &tam) {
        marked[v] = true;
        ++tam;
        for (int w : G.ady(v)) {
            if (!marked[w])
                busqProfundidad(G, w, tam);
        }
    }
};

void resuelveCaso(){
    int V, E;
    std::cin >> V >> E;
    
    Grafo grafo(V);
    int v, w;
    
    for (int i = 0; i < E; ++i) {
        std::cin >> v >> w;
        grafo.ponArista(v - 1, w - 1);
    }
    
    MaxCompCon max(grafo);
    std::cout << max.maximo() << "\n";
}

int main() {// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    int n = 0;
    std::cin >> n;
    
    for (int i = 0; i < n; ++i)
        resuelveCaso();
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
