
// Mauricio Abbati Loureiro

// Explicación de la solución y su coste

#include <iostream>
#include <fstream>
#include <limits>
#include "GrafoDirigidoValorado.h"
#include "IndexPQ.h"
using namespace std;


int resolver(const GrafoDirigidoValorado<int> &G, int tiempo, int S) {
 
    std::vector<int> distTo(G.V(), std::numeric_limits<int>::max());
    IndexPQ<int, std::less<int>> pq(G.V());
    
    distTo[S] = 0;
    pq.push(S, 0);
    
    while (!pq.empty()) {
        int v = pq.top().elem;
        pq.pop();
        for (AristaDirigida<int> e : G.ady(v)) {
            int v = e.from(), w = e.to();
            if (distTo[w] > distTo[v] + e.valor()) {
                distTo[w] = distTo[v] + e.valor();
                pq.update(w, distTo[w]);
            }
        }
    }
    
    int cuantos = 0;
    
    for (int i = 1; i < G.V(); ++i) {
        if (distTo[i] <= tiempo && i != S)
            ++cuantos;
    }
    
    return cuantos;
}

bool resuelveCaso() {
   int N, S, T, P;
   cin >> N >> S >> T >> P;
   
   if (!cin)
      return false;

   GrafoDirigidoValorado<int> g(N + 1);

   for (int i = 0; i < P; ++i) {
	   int A, B, coste;
	   std::cin >> A >> B >> coste;
	   AristaDirigida<int> temp(A, B, coste);
	   g.ponArista(temp);
   }
    
    GrafoDirigidoValorado<int> gInv = g.inverso();

   std::cout << resolver(gInv, T, S) << "\n";
   
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
