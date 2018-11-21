#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

bool resuelveCaso() {
	int n;
	std::cin >> n;

	if (n == 0) return false;

	int sol = 0;
	std::vector<int> altura, longitud;

	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		altura.push_back(temp);
	}

	for (int i = 0; i < n; ++i) {
		int temp;
		std::cin >> temp;
		longitud.push_back(temp);
	}

	std::sort(altura.begin(), altura.end());
	std::sort(longitud.begin(), longitud.end());

	for (int i = 0; i < altura.size(); ++i)
		sol += std::abs((altura[i] - longitud[i]));

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
	//system("PAUSE");
#endif
	return 0;
}
