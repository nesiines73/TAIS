#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"


int resuelve(std::string const& word1, std::string const& word2) {
    const int N = word1.size(), M = word2.size();
    Matriz<int> mat(N + 1, M + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        for (int f = 1; f <= M; ++f) {
            if (word1[N - i] == word2[M - f])
                mat[i][f] = mat[i - 1][f - 1] + 1;
            else
                mat[i][f] = std::max(mat[i - 1][f], mat[i][f - 1]);
        }
    }
    

    return mat[N][M];
}


bool resuelveCaso() {
    std::string word1, word2;
    std::cin >> word1 >> word2;
    
    if (!std::cin) return false;
   
    std::cout << resuelve(word1, word2) << "\n";
    
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
