//TAIS57
#include <iostream>
#include <vector>
#include <fstream>

/*
     Coste O(L)
     varillas[j] = varillas[j] si longitud de varilla j > j
     varillas[j] = varillas[j] || varillas[j - listaVarillas[i].longitud] si longitud de varilla j < j con que una de las dos sea manera nos vale para ver si podemos llegar a L.
     varillas[j]= 1 (o true) si longitud de varilla j = j ya que podemos utilizar esa varilla.
 */
bool esPosible(const std::vector<int> &varillas, const int &L) {
    
    std::vector<bool> posible(L + 1, false);
    posible[0] = true;
    
    for (int i = 1; i <= varillas.size(); ++i) {
        for (int j = L; j >= 1; --j) {
            if (varillas[i - 1] <= j)
                posible[j] = posible[j] || posible[j - varillas[i - 1]];
        }
    }
    return posible[L];
}

/*
     Coste O(L)
     varillas[j] = varillas[j] si longitud de varilla j > j
     varillas[j] = varillas[j] + varillas[j - listaVarillas[i].longitud] si longitud de varilla j <= j ahora sumamos ya ambas son maeras de llegar a la varilla L.
 */
int formas(const std::vector<int> &varillas, const int &L) {
    std::vector<int> formas(L + 1, 0);
    
    formas[0] = 1;
    
    for (int i = 1; i <= varillas.size(); ++i) {
        for (int j = L; j >= 1; --j) {
            if (varillas[i - 1] <= j)
                formas[j] = formas[j] + formas[j - varillas[i - 1]];
        }
    }
    return formas[L];
}

/*
     Coste O(L)
     varillas[j]= varillas[j] si longitud de varilla j > j
     varillas[j]= std::min(varillas[j] , varillas[j - listaVarillas[i].longitud]+1) nos quedamos con la menor de las dos maneras.
 */
int nVarillas(const std::vector<int> &varillas, const int &L) {
    std::vector<int> nVarillas(L + 1, 1e9);
    
    nVarillas[0] = 0;
    
    for (int i = 1; i <= varillas.size(); ++i) {
        for (int j = L; j >= 1; --j) {
            if (varillas[i - 1] <= j)
                nVarillas[j] = std::min(nVarillas[j], nVarillas[j - varillas[i - 1]] + 1);
        }
    }
    return nVarillas[L];
}

/*
     Coste O(L)
     varillas[j] = varillas[j] si longitud de varilla j > j
     varillas[j] = std::min(varillas[j] , varillas[j - listaVarillas[i].longitud] + listaVarillas[i].longitud] + listaVarillas[i].precio)  si longitud de varilla j >= j
     nos quedamos con la menor de las dos maneras, pero ahora teniendo en cuenta el precio.
 */
int precio(const std::vector<int> &varillas, const int &L, const std::vector<int> &precios) {
    
    std::vector<int> precio(L + 1, 1e9);
    precio[0] = 0;
        
    for (int i = 1; i <= varillas.size(); ++i) {
        for (int j = L; j >= 1; --j) {
            if (varillas[i - 1] <= j)
                precio[j] = std::min(precio[j], precio[j - varillas[i - 1]] + precios[i - 1]);
        }
    }
    return precio[L];
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
