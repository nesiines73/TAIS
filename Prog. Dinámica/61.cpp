#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

/*
 
 cazatesoros(i,j) = cantidad máxima de cofres i que se pueden recuperar en el tiempo j.
 
 Casos bases:
    cazatesoros(i,0) = 0
    cazatesoros(0,j) = 0
 
 Caso recursivo:
     cazatesoros(i,j) = cazatesoros(i-1,j) si tiempo[i] > j
     cazatesoros(i,j) = max(cazatesoros(i-1,j), cazatesoros(i-1,j-tiempo[i]) + oro[i]) si tiempo[i] <= j
 
 Coste:
    O(n*T) tanto en espacio como en tiempo, siendo n los cofres y T los tiempos.
 
*/

struct Tesoro {
    int tiempo;
    int oro;
};

void recogeTesoros(std::vector<Tesoro> const& tesoros, int T, int & maximoRecogible, int & cuantos, std::vector<bool> & cuales) {
    int N = tesoros.size() - 1;
    Matriz<int> cazatesoros(N + 1, T + 1, 0);
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= T; ++j) {
            if (tesoros[i].tiempo > j)
                cazatesoros[i][j] = cazatesoros[i - 1][j];
            else
                cazatesoros[i][j] = std::max(cazatesoros[i - 1][j], cazatesoros[i - 1][j - tesoros[i].tiempo] + tesoros[i].oro);
        }
    }
    maximoRecogible = cazatesoros[N][T];
    
    int resto = T;
    for (int i = N; i >= 1; --i) {
        if (cazatesoros[i][resto] == cazatesoros[i - 1][resto]) {
            cuales[i] = false;
        }
        else {
            cuales[i] = true;
            resto = resto - tesoros[i].tiempo;
            ++cuantos;
        }
    }
}

bool resuelveCaso() {
    int T, N;
    std::cin >> T >> N;
    
    if (!std::cin) return false;
    
    std::vector<Tesoro> tesoros(N + 1);
    for (int i = 1; i <= N; i++) {
        std::cin >> tesoros[i].tiempo >> tesoros[i].oro;
        tesoros[i].tiempo *= 3;
    }
    
    int maximoRecogible = 0, cuantos = 0;
    std::vector<bool> cuales(N + 1);
    recogeTesoros(tesoros, T, maximoRecogible, cuantos, cuales);
    
    std::cout << maximoRecogible << "\n";
    std::cout << cuantos << "\n";
    for (int i = 1; i <= N; ++i) {
        if (cuales[i])
            std::cout << tesoros[i].tiempo / 3 << " " << tesoros[i].oro << "\n";
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
