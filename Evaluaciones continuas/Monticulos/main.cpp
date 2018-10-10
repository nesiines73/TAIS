
// Mauricio Abbati Loureiro
// Cristóbal Saraiba Torres

// Explicación de la solución y su coste
/*
Lo que se hace es una priority queue de las cajas actuales y una cola con los clientes en las
que se pone su tiempo, los clientes se van asignando a las cajas y cuando las cajas se han agotado
se expulsa al cliente que menos tiempo tarda y se agrega al siguiente que hay en la cola.
Coste O(n)
*/

#include <iostream>
#include <fstream>
#include <queue>
#include "PriorityQueue.h"
using namespace std;

class Cajas {
public:
	struct caja {
		int orden;
		int tiempo;
	};

	bool operator() (const caja &c1, const caja &c2) {
		return c1.tiempo < c2.tiempo;
	}


};

bool resuelveCaso() {
   int N, C;
   cin >> N >> C;
   
   if (N == 0)
      return false;

   PriorityQueue<Cajas::caja, Cajas> cola;
   std::queue<int> clientes;

   for (int i = 0; i < C; ++i) {
	   int tiempo;
	   std::cin >> tiempo;
	   clientes.push(tiempo);
   }

   if (C < N) {
	   std::cout << C + 1 << "\n";
	   return true;
   }

   for (int i = 0; i < C; ++i) {
	   if (i >= N) {
		   int caja = cola.top().orden;
		   cola.pop();
		   cola.push({ caja, clientes.front() });
	   }
	   else {
		   cola.push({ i + 1, clientes.front() });
	   }
	   clientes.pop();
   }

   std::cout << cola.top().orden << "\n";
   // completa para terminar de leer y resolver un caso
   
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
   system("PAUSE");
#endif
   return 0;
}
