#include <iostream>
#include <vector>
#include <fstream>
#include "Matriz.h"

bool esPosible(const std::vector<int> &varillas, const int &L) {
    
    Matriz<bool> posible(varillas.size(), L + 1, false);
    posible[0][0] = true;
    
    for (int i = 1; i <= varillas.size() - 1; ++i) {
        posible[i][0] = true;
        for (int j = 1; j <= L; ++j) {
            if (varillas[i] > j)
                posible[i][j] = posible[i - 1][j];
            else
                posible[i][j] = (posible[i - 1][j]) ? posible[i - 1][j] : posible[i - 1][j - varillas[i]];
        }
    }
    return posible[varillas.size() - 1][L];
}

int formas(const std::vector<int> &varillas, const int &L) {
    Matriz<int> formas(varillas.size(), L + 1, 0);
    
    formas[0][0] = 1;
    
    for (int i = 1; i <= varillas.size() - 1; ++i) {
        formas[i][0] = 1;
        for (int j = 1; j <= L; ++j) {
            if (varillas[i] > j)
                formas[i][j] = formas[i - 1][j];
            else
                formas[i][j] = formas[i - 1][j] + formas[i - 1][j - varillas[i]];
        }
    }
    return formas[varillas.size() - 1][L];
}

int nVarillas(const std::vector<int> &varillas, const int &L) {
    Matriz<int> nVarillas(varillas.size(), L + 1, 1e9);
    
    nVarillas[0][0] = 0;
    
    for (int i = 1; i <= varillas.size() - 1; ++i) {
        nVarillas[i][0] = 0;
        for (int j = 1; j <= L; ++j) {
            if (varillas[i] > j)
                nVarillas[i][j] = nVarillas[i - 1][j];
            else
                nVarillas[i][j] = std::min(nVarillas[i - 1][j], nVarillas[i - 1][j - varillas[i]] + 1);
        }
    }
    return nVarillas[varillas.size() - 1][L];
}

int precio(const std::vector<int> &varillas, const int &L, const std::vector<int> &precios) {
    Matriz<int> precio(varillas.size(), L + 1, 1e9);
    precio[0][0] = 0;
        
    for (int i = 1; i <= varillas.size() - 1; ++i) {
        precio[i][0] = 0;
        for (int j = 1; j <= L; ++j) {
            if (varillas[i] > j)
                precio[i][j] = precio[i - 1][j];
            else
                precio[i][j] = std::min(precio[i - 1][j], precio[i - 1][j - varillas[i]] + precios[i]);
        }
    }
    return precio[varillas.size() - 1][L];
}

bool resuelveCaso() {
    int n, L;
    std::cin >> n >> L;
    
    if (!std::cin) return false;
    
    std::vector<int> v(n + 1, 0);
    std::vector<int> p(n + 1, 0);
    for (size_t i = 1; i < n + 1; ++i) {
        std::cin >> v[i];
        std::cin >> p[i];
    }
    
    if (esPosible(v, L)) std::cout << "SI " << formas(v, L) << " " << nVarillas(v, L) << " " << precio(v, L, p) << "\n";
    else std::cout << "NO\n";
    
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
