#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool resuleveCaso() {
    int n, res = 0;
    
    std::cin >> n;
    
    if (!std::cin) return false;
    
    std::vector<int> v(n);
    
    for (int i = 0; i < v.size(); ++i)
        std::cin >> v[i];
    
    std::sort(v.begin(), v.begin() + n, std::greater<int>());
    
    int aux = 0;
    for (int i = 0; i < v.size() && aux < v.size(); ++i) {
        for (int d = aux + 2; d < aux + 3 && d < v.size(); d = d + 3)
            res += v[d];
        aux = aux + 3;
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
