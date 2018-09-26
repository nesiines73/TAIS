#include <fstream>
#include <iostream>
#include <vector>

#include "TreeMap_AVLTamI.h"



bool resuleveCaso() {
	unsigned int numElem;

	std::cin >> numElem;
	if (numElem == 0) return false;

	int claves;
	int m;
	int posicion;

	map<int, int, std::less<int>> arbol;
	for (int i = 0; i < numElem; i++) {
		std::cin >> claves;
		arbol.insert(claves);
	}

	std::cin >> m;
	//arbol.print();
	for (int j = 0; j < m; j++) {
		std::cin >> posicion;
		int claves = arbol.k_esimo(posicion);
		if (claves == -1) std::cout << "??\n";
		else std::cout << claves << '\n';
	}

	std::cout << "----\n";

	return true;
}

int main() {// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuleveCaso());
	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	//system("PAUSE");
#endif
	return 0;
}
