#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

struct Tesoro {
    int prof;
    int cant;
};

void recogeTesoros(std::vector<Tesoro> const& tesoros, int T, int & maximoRecogible, int & cuantos, std::vector<bool> & cuales) {
    int n = tesoros.size() - 1;
    Matriz<int> mochila(n + 1, T + 1, 0);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= T; ++j) {
            if (tesoros[i].prof * 3 > j)
                mochila[i][j] = mochila[i - 1][j];
            else
                mochila[i][j] = std::max(mochila[i - 1][j], mochila[i - 1][j - (tesoros[i].prof * 3)] + tesoros[i].cant);
        }
    }
    maximoRecogible = mochila[n][T];
    
    int resto = T;
    for (int i = n; i >= 1; --i) {
        if (mochila[i][resto] == mochila[i - 1][resto]) {
            cuales[i] = false;
        }
        else {
            cuales[i] = true;
            resto = resto - (tesoros[i].prof * 3);
            cuantos++;
        }
    }
}

bool resuelveCaso() {
    int T, N;
    std::cin >> T >> N;
    
    if (!std::cin) return false;
    
    std::vector<Tesoro> tesoros(N + 1);
    for (int i = 1; i <= N; i++) {
        std::cin >> tesoros[i].prof >> tesoros[i].cant;
    }
    
    int maximoRecogible = 0, cuantos = 0;
    std::vector<bool> cuales(N + 1);
    recogeTesoros(tesoros, T, maximoRecogible, cuantos, cuales);
    
    std::cout << maximoRecogible << "\n";
    std::cout << cuantos << "\n";
    for (int i = 1; i <= N; ++i) {
        if (cuales[i])
            std::cout << tesoros[i].prof << " " << tesoros[i].cant << "\n";
    }
    std::cout << "----\n";
    
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
