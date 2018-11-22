#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

bool mayor(int a, int b) {
    return a > b;
}

bool resuelveCaso() {
    int n;
    std::cin >> n;
    
    if (n == 0) return false;
    
    int sol = 0;
    std::vector<int> rivales, broncos;
    
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        rivales.push_back(temp);
    }
    
    for (int i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        broncos.push_back(temp);
    }
    
    std::sort(rivales.begin(), rivales.end());
    std::sort(broncos.begin(), broncos.end(), mayor);
    
    int aux = 0;
    for (int i = 0; i < broncos.size(); ++i){
        bool continua = true;
        for (int j = aux; j < rivales.size() && continua; ++j){
            ++aux;
            if (broncos[i] >= rivales[j]){
                sol += broncos[i] - rivales[j];
                continua = false;
            }
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
    
    while (resuelveCaso());
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
