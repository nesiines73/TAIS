#include <fstream>
#include <iostream>
#include <vector>

#include "PriorityQueue.h"

unsigned long long int resuelve(PriorityQueue<unsigned long long int> &cola, const unsigned int &n) {
	if (cola.empty()) return 0;
	unsigned long long int aux1 = 0, aux2 = 0, total = 0;

	for (unsigned int i = 0; i < n - 1 &&!cola.empty(); ++i) {
		aux1 = cola.top();
		cola.pop();
		aux2 = cola.top();
		cola.pop();
		cola.push((aux1 + aux2));
		total += aux1 + aux2;
	}

	return total;
}

bool resuleveCaso() {

	unsigned int n;
	std::cin >> n;

	if (n == 0) return false;

	PriorityQueue<unsigned long long int> cola;

	for (unsigned int i = 0; i < n; ++i) {
		unsigned int sumandos;
		std::cin >> sumandos;
		cola.push(sumandos);
	}

	std::cout << resuelve(cola, n) << '\n';

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
