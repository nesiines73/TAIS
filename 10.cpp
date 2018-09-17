#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <algorithm> 
#include "bintree_eda.h" 

 
unsigned int altura(bintree<char> arbol, bool &ok) { 
	if (arbol.empty())
		return 0; 
	else {
		unsigned int altIz = altura(arbol.left(), ok); 
		unsigned int altDr = altura(arbol.right(), ok); 
		if (altDr != altIz && altDr != altIz - 1 && altDr != altIz + 1)
			ok = false; 
		return 1 + std::max(altIz, altDr); 
	} 
} 
 
void resuleveCaso() { 
	auto arbol = leerArbol('.'); 
	bool equilibrado = true; 
	altura(arbol, equilibrado); 
	 
	if (equilibrado) std::cout << "SI" << "\n"; 
	else std::cout << "NO" << "\n"; 
} 
 
int main() {
	// ajustes para que cin extraiga directamente de un fichero 
	#ifndef DOMJUDGE 
	std::ifstream in("casos.txt"); 
	auto cinbuf = std::cin.rdbuf(in.rdbuf()); 
	#endif 
	int numCasos; 
	std::cin >> numCasos; 
	for (int i = 0; i < numCasos; ++i) 
		resuleveCaso(); 
	// para dejar todo como estaba al principio 
	#ifndef DOMJUDGE 
		std::cin.rdbuf(cinbuf); 
		system("PAUSE"); 
	#endif 
	return 0; 
} 