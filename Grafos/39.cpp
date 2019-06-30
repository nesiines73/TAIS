#include <iostream>
#include <fstream>
#include <queue>
#include <limits>
#include "IndexPQ.h"
#include "GrafoDirigidoValorado.h"

const int MAX = std::numeric_limits<int>::max();

//Dijkstra
class Amazon {
public:
    Amazon (const GrafoDirigidoValorado<int> & GDV, int o) : distTo(GDV.V(), MAX),
    pq(GDV.V()), esPosible(true), tiempo(0), distGoBack(GDV.V(), MAX) {
        
        GrafoDirigidoValorado<int> inverso = GDV.inverso();
        
        distGoBack[o] = 0;
        pq.push(o, 0.0);
        
        while (!pq.empty()) {
            auto v = pq.top();
            pq.pop();
            for (auto w : inverso.ady(v.elem))
                relaxInv(w);
        }
        
        distTo[o] = 0;
        pq.push(o, 0.0);
        
        while (!pq.empty()) {
            auto v = pq.top();
            pq.pop();
            for (auto w : GDV.ady(v.elem))
                relax(w);
        }
    }
    
    int getSol(const int &o, const std::vector<int> &sended) {
        for (int i = 1; i < sended.size(); ++i){
            if (distTo[sended[i]] == MAX || distGoBack[sended[i]] == MAX)
                esPosible = false;
            tiempo += distTo[sended[i]] + distGoBack[sended[i]];
        }
        if (!esPosible) return -1;
        else return tiempo;
    }
    
    
private:
    int tiempo;
    bool esPosible;
    IndexPQ<double> pq;
    std::vector<int> distTo;
    std::vector<int> distGoBack;
    
    void relax(const AristaDirigida<int> & e) {
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.valor()) {
            distTo[w] = distTo[v] + e.valor();
            pq.update(e.to(), distTo[w]);
        }
        
    }
    void relaxInv(const AristaDirigida<int> & e) {
        int v = e.from(), w = e.to();
        if (distGoBack[w] > distGoBack[v] + e.valor()) {
            distGoBack[w] = distGoBack[v] + e.valor();
            pq.update(e.to(), distGoBack[w]);
        }
        
    }
};

bool resuelveCaso() {
    int N, C, O, R;
    std::cin >> N;
    
    if (!std::cin) return false;
    
    std::cin >> C;
    
    GrafoDirigidoValorado<int> g(N + 1);
    
    for (int i = 0; i < C; ++i) {
        int A, B, coste;
        std::cin >> A >> B >> coste;
        g.ponArista(AristaDirigida<int>(A, B, coste));
    }
    
    std::cin >> O >> R;
    
    std::vector<int> repartos(R + 1);
    
    for (int i = 1; i <= R; ++i)
        std::cin >> repartos[i];
    
    Amazon prime(g, O);
    
    int sol = prime.getSol(O, repartos);
    if (sol == -1) std::cout << "Imposible\n";
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
