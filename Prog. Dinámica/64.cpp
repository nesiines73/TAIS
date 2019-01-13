#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"


std::string resuelve(std::string const& word) {
    int n = word.length();
    Matriz<int> longitudPalindromos(n, n, 0);
    
    for (int i = 0; i < n; i++)
        longitudPalindromos[i][i] = 1;
    
    for (int d = 1; d < n; ++d) { // recorre diagonales
        for (int i = 0; i < n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            if (word[i] == word[j])
                longitudPalindromos[i][j] = longitudPalindromos[i + 1][j - 1] + 2;
            else
                longitudPalindromos[i][j] = std::max(longitudPalindromos[i + 1][j], longitudPalindromos[i][j - 1]);
        }
    }
    
    int max = longitudPalindromos[0][n - 1];
    std::string resultado(max, '\0');
    
    int j = n - 1, i = 0, pos = 0;
    while (pos * 2 < max) {
        if (max - (pos * 2) == 1) {
            resultado[pos] = word[j];
            pos++;
            i++;
            j--;
        }
        else {
            if (word[i] == word[j]) {
                resultado[pos] = word[j];
                resultado[max - pos - 1] = word[j];
                pos++;
                i++;
                j--;
            }
            else if (longitudPalindromos[i][j - 1] <= longitudPalindromos[i + 1][j])
                i++;
            else
                j--;
        }
    }
    return resultado;
}


bool resuelveCaso() {
    std::string word;
    std::cin >> word;
    
    if (!std::cin) return false;
   
    std::cout << resuelve(word) << "\n";
    
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
