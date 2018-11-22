#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

bool resuelveCaso() {
    int n, v;
    std::cin >> n >> v;
    std::vector<int> pilas;
    
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        pilas.push_back(temp);
    }
    
    int sol = 0;
    
    std::sort(pilas.begin(), pilas.end());
    
    int cantidadPilas = n - 1;
    for (int i = 0; i < pilas.size() && cantidadPilas >= 0 && i < cantidadPilas; ++i){
        if (pilas[i] + pilas[cantidadPilas] >= v) {
            --cantidadPilas;
            ++sol;
        }
    }

    
    std::cout << sol << "\n";
    
    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    int casos = 0;
    std::cin >> casos;
    for (int i = 0; i < casos; ++i)
        resuelveCaso();
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
