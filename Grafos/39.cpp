#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include "IndexPQ.h"
#include "GrafoDirigidoValorado.h"

//Dijkstra
int resuelve(const GrafoDirigidoValorado<int> &G, const std::vector<int> &repartos, const int &O) {
    std::vector<AristaDirigida<int>> edgeTo(G.V(), {0 , 0, std::numeric_limits<int>::max()});
    std::vector<int> distTo(G.V(), std::numeric_limits<int>::max());
    IndexPQ<int, std::less<int>> pq(G.V());
    bool imposible = false;
    
    distTo[O] = 0;
    pq.push(O, 0);
    
    while (!pq.empty()) {
        int v = pq.top().elem;
        pq.pop();
        for (AristaDirigida<int> e: G.ady(v)) {
            int v = e.from(), w = e.to();
            if (distTo[w] > distTo[v] + e.valor()) {
                distTo[w] = distTo[v] + e.valor();
                pq.update(w, distTo[w]);
            }
            AristaDirigida<int> temp(e.from(), e.to(), distTo[v] + e.valor());
            if (edgeTo[e.from()].valor() > temp.valor())
                edgeTo[e.from()] = temp;
        }
    }
    
    for (int i = 1; i < repartos.size() && !imposible; ++i) {
        if (edgeTo[repartos[i]].to() == 0)
            imposible = true;
        else if (edgeTo[repartos[i]].to() != O) {
            int from = repartos[i], to = edgeTo[repartos[i]].to();
            while (to != from && to != O) {
                from = edgeTo[repartos[i]].to();
                to = edgeTo[from].to();
            } if (to != O)
                imposible = true;
            else
                distTo[O] += edgeTo[from].valor() ;
        }
        else
            distTo[O] += edgeTo[repartos[i]].valor();
    }
    
    if (imposible) return -1;
    return distTo[O];
    
}

bool resuelveCaso() {
    int N, C, O, R;
    std::cin >> N;
    
    if (!std::cin) return false;
    
    std::cin >> C;
    
    GrafoDirigidoValorado<int> g(N + 1);
    
    for (int i = 0; i < C; ++i) {
        int A, B, coste;
        std::cin >> A >> B >> coste;
        AristaDirigida<int> temp(A, B, coste);
        g.ponArista(temp);
    }
    
    std::cin >> O >> R;
    
    std::vector<int> repartos(R + 1);
    
    for (int i = 1; i <= R; ++i)
        std::cin >> repartos[i];
    
    if (g.V() == 2) std::cout << "Imposible\n";
    
    else {
        int sol = resuelve(g, repartos, O);
        
        if (sol == -1) std::cout << "Imposible\n";
        else std::cout << sol << "\n";
    }
    
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
