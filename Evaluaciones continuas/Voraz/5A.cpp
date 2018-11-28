
// Mauricio Abbati Loureiro
// Usuario examen: TAIS29
// Usuario Juez normal: TAIS57

/* 
	Hacemos una PriorityQueue ordenada de menor a mayor.
	Comparamos si el la talla del jugador actual es igual que la talla disponible actual o la talla disponible supera
	en una unidad la del jugador.
	Si la talla es menor, no va a haber otro jugador posteriormente que le sirva esa talla, así que la descartamos.
	Si la talla es igual que la condición correcta, descartamos al jugador y la talla (asignación).
	Si la talla es muy grande pues hay que comprar otra equipación.
	Si al acabarse las tallas disponibles queda algún jugador desnudo, pues hay que comprarle equipamento.
	Si se acaban los jugadores y sobran equipamento, mejor.

	Coste: O(nlogn)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "PriorityQueue.h"


bool resuelveCaso() {
   int N, M;
   std::cin >> N >> M;
   
   if (!std::cin)
      return false;

   PriorityQueue<int> tallasJugador, tallasDisponibles;

   for (int i = 0; i < N; ++i) {
	   int aux;
	   std::cin >> aux;
	   tallasJugador.push(aux);
   }

   for (int i = 0; i < M; ++i) {
	   int aux;
	   std::cin >> aux;
	   tallasDisponibles.push(aux);
   }

   int sol = 0, aux = 0;

   while (!tallasJugador.empty() && !tallasDisponibles.empty()) {
	   int tallaJugador = tallasJugador.top(), tallaDisp = tallasDisponibles.top();
	
	   if (tallaDisp < tallaJugador) {
		   tallasDisponibles.pop(); //Esa talla no le servirá a ningún otro jugador y se descarta.
	   }
	   else if (tallaDisp == tallaJugador || tallaDisp == tallaJugador + 1) {
		   tallasDisponibles.pop(); //Asignamos la prenda al jugador descartando ambos.
		   tallasJugador.pop();
	   }
	   else {
		   ++sol; //Compras una y el jugador se descarta.
		   tallasJugador.pop();
	   }
   } 

   if (!tallasJugador.empty())
	   sol += tallasJugador.size();
   
   std::cout << sol << "\n";
   
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
