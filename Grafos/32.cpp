#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include "GrafoDirigido.h"

using Path = std::deque<size_t>;

class BreadthFirstDirectedPaths {
public:
    BreadthFirstDirectedPaths(GrafoDirigido const& G, int s) : marked(G.V(), false), distTo(G.V()) {
        bfs(G, s); }
    // ¿Hay camino del origen a v?
    bool hayCamino(int v) const {
        return marked[v];
    }
    // número de aristas entre s y v
    int distancia(int v) const {
        return distTo[v];
    }

private:
    std::vector<bool> marked; // marked[v] = ¿hay camino de s a v?
    std::vector<int> distTo;  // distTo[v] = aristas en el camino s-v más corto
    void bfs(GrafoDirigido const& G, int s) {
        std::queue<int> q;
        distTo[s] = 0;
        marked[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : G.ady(v)) {
                if (!marked[w]) {
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                } }
        } }
};

bool resuelveCaso(){
    
    int n, k, s, e, vertices;
    
    std::cin >> n >> k >> s >> e;
    if (n == 0) return false;
    
    std::vector<int> finAtajo(n * n + 1, -1);
    vertices = (n * n + 1);
    GrafoDirigido grafo(vertices);
    for (int i = 0; i < s + e; ++i){//serpientes y escaleras
        int v, w;
        std::cin >> v >> w;
        finAtajo[v] = w;
    }
    for (int i = 1; i <= n * n; ++i){//paso de casilla en casilla
        for (int j = 1; j <= k; j++){
            int extremo = i + j;
            if ( extremo <= n*n){
                if (finAtajo[extremo] != -1)
                    grafo.ponArista(i, finAtajo[extremo]);
                else
                    grafo.ponArista(i, extremo);
            }
        }
    }
    
    BreadthFirstDirectedPaths Breadth(grafo, 1);
    if (grafo.E() == 0)
        std::cout << "1" << std::endl;
    else
        std::cout << Breadth.distancia(n * n) << std::endl;
    
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
