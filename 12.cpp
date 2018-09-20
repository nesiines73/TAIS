#include <fstream>
#include <iostream>
#include <vector>

#include "TreeMap_AVL.h"

template <typename Clave, typename Valor, typename Comparador = std::less<Clave>>
class TreeMapRan : public map<Clave, Valor, Comparador> {
public:
    
	TreeMapRan(Comparador c = Comparador()) : map<Clave, Valor, Comparador>(c) {};
    
    std::vector<Clave> rango(Clave const& k1, Clave const& k2) const {
        std::vector<Clave> rango;
        this->rango(k1-1, k2+1, this->raiz, rango);
        return rango;
    }
    
protected:
	using TreeNode = typename map<Clave, Valor, Comparador>::TreeNode;
    using Link = TreeNode *;
    
    void rango(Clave const& k1, Clave const& k2, Link a, std::vector<Clave> & lista) const {
        if (a == nullptr)
            return;
        if (a->iz != nullptr && this->menor(k1, a->cv.clave))
            rango(k1, k2, a->iz, lista);
        if (this->menor(k1, a->cv.clave) && this->menor(a->cv.clave, k2))
            lista.push_back(a->cv.clave);
        if (a->dr != nullptr && this->menor(a->cv.clave, k2))
            rango(k1, k2, a->dr, lista);
    }
};


bool resuleveCaso() {
	TreeMapRan<int, int, std::less<int>> arbol;
	int numElem, clave, k1, k2;
	std::vector<int> lista;

	std::cin >> numElem;
	if (numElem <= 0) return false;

	for (int i = 0; i < numElem; i++){
		std::cin >> clave;
		arbol.insert(clave);
	}

	std::cin >> k1 >> k2;

	lista = arbol.rango(k1, k2);

	std::vector<int>::const_iterator it = lista.cbegin();

	if (!lista.empty()){
		while (it != lista.cend()){
			std::cout << *it;
			++it;
			if (it != lista.cend())
				std::cout << " ";
		}
	}
	std::cout << '\n';
	return true;
}

int main() {// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
        std::ifstream in("casos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    
    while(resuleveCaso());
    // para dejar todo como estaba al principio
    #ifndef DOMJUDGE
        std::cin.rdbuf(cinbuf);
        //system("PAUSE");
    #endif
    return 0;
}
