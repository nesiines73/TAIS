#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"

bool resolver(const GrafoValorado<int> &ciudad, const Arista<int> &camion, const int &posicion, std::vector<bool> &alcance) {
    
	AdysVal<int> ady = ciudad.ady(posicion);
	bool solucion = false;
    
	for (int i = 0; i < ady.size() && !solucion; i++) {
		if (ady.at(i).valor() >= camion.valor()) {
			int otro = ady.at(i).otro(posicion);
			if (otro == camion.otro(camion.uno()))
				return true;
			if (alcance.at(otro) == false) {
				alcance.at(otro) = true;
				solucion = resolver(ciudad, camion, otro, alcance);
			}
		}
	}
    
	return solucion;
}


bool resuelveCaso() {
	int V, E, K;
	std::cin >> V >> E;

	if (!std::cin) return false;
	
	GrafoValorado<int> ciudad = GrafoValorado<int>(V+1);
	
	int A, B, coste;
	Arista<int> temp;

	for (int i = 1; i <= E; i++) {
		std::cin >> A >> B >> coste;
		temp = Arista<int>(A, B, coste);
		ciudad.ponArista(temp);
	}

	std::cin >> K;
	for (int i = 1; i <= K; i++) {
		std::cin >> A >> B >> coste;
		std::vector<bool> alcance = std::vector<bool>(V + 1, false);
		alcance.at(A) = true;
		temp = Arista<int>(A, B, coste);

		if (resolver(ciudad, temp, A, alcance))
			std::cout << "SI\n";
		else
			std::cout << "NO\n";
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
