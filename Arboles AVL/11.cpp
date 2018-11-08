#include <fstream> 
#include <sstream> 
#include <iostream> 
#include <algorithm> 
#include "bintree_eda.h" 

 
unsigned int altura(bintree<int> arbol, bool &ok) { 
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

bool esMenor(bintree<int> arbol, int val) {

	if (arbol.empty()) return true;
	return arbol.root() < val && esMenor(arbol.left(), val) && esMenor(arbol.right(), val);
}

bool esMayor(bintree<int> arbol, int val) {

	if (arbol.empty()) return true;
	return arbol.root() > val && esMayor(arbol.left(), val) && esMayor(arbol.right(), val);
}

bool esBusqueda(bintree<int> arbol) {

	if (arbol.empty()) return true;

	return esMenor(arbol.left(), arbol.root()) && esMayor(arbol.right(), arbol.root())
		&& esBusqueda(arbol.left()) && esBusqueda(arbol.right());
}
 
void resuleveCaso() { 
	auto arbol = leerArbol(-1); 
	bool equilibrado = true; 
	altura(arbol, equilibrado); 
	 
	if (equilibrado && esBusqueda(arbol)) std::cout << "SI" << "\n"; 
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