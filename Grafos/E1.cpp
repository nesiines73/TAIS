//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <queue>
#include "IndexPQ.h"
#include "GrafoDirigidoValorado.h"


//COSTE TOTAL (V + (E log V))

//Dijkstra
//Coste (E log V)
class MejorCamino {
    std::vector<AristaDirigida<int>> edgeTo;
    std::vector<int> distTo;
    std::vector<bool> marcas;
    IndexPQ<int> pq;
    int origen;
    
    void relax(const AristaDirigida<int> &e) {
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.valor()) {
            distTo[w] = distTo[v] + e.valor();
            edgeTo[w] = e;
            pq.update(w, distTo[w]);
        }
    }
    
public:
    
    MejorCamino(GrafoDirigidoValorado<int> G, int s): origen(s), edgeTo(G.V()), distTo(G.V(), std::numeric_limits<int>::max()), marcas(G.V(), false), pq(G.V()) {
        
        distTo[s] = 0;
        pq.push(s, 0);
        
        while(!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (AristaDirigida<int> e : G.ady(v))
                relax(e);
        }
    }
    
    bool hayCamino(int v) {
        return distTo[v] != std::numeric_limits<int>::max();
    }
    
    int costeCamino(int v) {
        return distTo[v];
    }
    
    int distanciaAOrigen(int w) {
        
        int sol = 0;
        while (w != origen) {
            ++sol;
            w = edgeTo[w].from();
        }
        return sol;
    }
};

//Coste (V + E)
class BusquedaAnchura {
    
    std::vector<bool> marked;
    std::vector<int> distTo;
    
    void bfs(GrafoDirigidoValorado<int> const &G,int s) {
        std::queue<int> q;
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for (AristaDirigida<int> w : G.ady(v)) {
                if(!marked[w.to()]) {
                    distTo[w.to()] = distTo[v] + 1;
                    marked[w.to()] =true;
                    q.push(w.to());
                }
            }
        }
    }
    
public:
    BusquedaAnchura(GrafoDirigidoValorado<int> const &G,int s): marked(G.V(),false), distTo(G.V()) {
        bfs(G, s);
    }
    
    bool hayCamino(int v) const{
        return marked[v];
    }
    
    int distancia(int v) const{
        return distTo[v];
    }
};


bool resuelveCaso() {
    int V, E, K;
    std::cin >> V >> E;
    
    if (!std::cin) return false;
    
    GrafoDirigidoValorado<int> Grafo(V + 1);
    
    for (int e = 1; e <= E; ++e) {
        int a, b, coste;
        std::cin >> a >> b >> coste;
        Grafo.ponArista(AristaDirigida<int>(a, b, coste));
        Grafo.ponArista(AristaDirigida<int>(b, a, coste));
    }
    
    std::cin >> K;
    for (int k = 0; k < K; ++k) {
        int o, d;
        std::cin >> o >> d;
        
        MejorCamino camino(Grafo, o);
        if (camino.hayCamino(d)) {
            std::cout << camino.costeCamino(d) << " ";
            BusquedaAnchura bfs(Grafo, o);
            if (bfs.distancia(d) == camino.distanciaAOrigen(d))
                std::cout << "SI\n";
            else
                std::cout << "NO\n";
        } else
            std::cout << "SIN CAMINO\n";
    }
    
    std::cout << "----\n";
    
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
