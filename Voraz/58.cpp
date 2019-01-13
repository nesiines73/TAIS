#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool resuleveCaso() {
    int peso, n, res = 0;
    
    std::cin >> peso >> n;
    
    if (!std::cin) return false;
    
    std::vector<int> v(n);
    
    for (int i = 0; i < v.size(); ++i)
        std::cin >> v[i];
    
    std::sort(v.begin(), v.begin() + n);
    
    int fin = v.size() - 1, ini = 0;
    while (ini <= fin) {
        int pesoAc = peso - v[fin];
        if (pesoAc >= v[ini]) {
            ++ini;
            --fin;
        } else
            --fin;
        ++res;
    }
    
    std::cout << res << "\n";
    
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
