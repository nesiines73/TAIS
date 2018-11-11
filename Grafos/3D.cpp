#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include "GrafoDirigidoValorado.h"

class Dijkstra{
private:
    
    std::vector<unsigned int> distTo;
    std::vector<int> numeroCaminos;
    IndexPQ<int> pq;
    
public:
    
    Dijkstra(const GrafoDirigidoValorado<int> &grafo, int s): pq(grafo.V()){
        
        distTo = std::vector<unsigned int>(grafo.V(), 4294967295);
        numeroCaminos = std::vector<int>(grafo.V(),0);
        distTo[s] = 0;
        numeroCaminos[s] = 1;
        pq.push(s,0);
        
        while (!pq.empty()){
            int v = pq.top().elem;
            pq.pop();
            for (AristaDirigida<int> e : grafo.ady(v))
                caminos(e);
        }
    }
    void caminos(const AristaDirigida<int> &e){
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.valor()){
            distTo[w] = distTo[v] + e.valor();
            
            numeroCaminos[w] = numeroCaminos[v];
            pq.update(w, distTo[w]);
            
        }
        else if (distTo[w] == distTo[v] + e.valor())
            numeroCaminos[w] += numeroCaminos[v];
    }
    
    int viasPosibles(int v){
        return numeroCaminos[v];
    }
    
};


bool resuelveCaso() {
    int V, E;
    std::cin >> V >> E;
    
    if (!std::cin) return false;
    
    GrafoDirigidoValorado<int> g(V + 1);
    
    for (int i = 0; i < E; ++i){
        int a, b, coste;
        std::cin >> a >> b >> coste;
        AristaDirigida<int> arista(a, b, coste);
        AristaDirigida<int> inversa(b, a, coste);
        g.ponArista(arista);
        g.ponArista(inversa);
    }
    
    Dijkstra d(g, 1);
    std::cout << d.viasPosibles(V) << "\n";
    
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
