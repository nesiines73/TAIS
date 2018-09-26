#include <fstream>
#include <iostream>
#include <vector>

#include "Multitarea.h"

bool resuleveCaso() {
	unsigned int tareasUnicas, tareasPeriodicas;
	unsigned long long int minutos;

	std::cin >> tareasUnicas;
	if (!std::cin) return false;
	
	ListaTareas tareas;

	std::cin >> tareasPeriodicas >> minutos;

	for (int i = 0; i < tareasUnicas; ++i) {
		unsigned int ini, fin;
		std::cin >> ini >> fin;
		tareas.insertar('U', ini, fin, minutos, 0);
	}

	for (int i = 0; i < tareasPeriodicas; ++i) {
		unsigned int ini, fin, repe;
		std::cin >> ini >> fin >> repe;
		tareas.insertar('P', ini, fin, minutos, repe);
	}

	/*while (!tareas.empty) {
		//Tarea aux;
	}*/

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
