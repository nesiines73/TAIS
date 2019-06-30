//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include "Matriz.h"

/*
 
 palindromo(i,j) = longitud máxima del palíndromo a partir de la palabra original que va de i a j.
 
 Caso base:
    palindromo(i,j) = 1 si i == j
 
 Caso recursivo:
    palindromo(i,j) = 2 + palindromo(i+1,j-1) si pal[i] == pal[j]
    palindromo(i,j) = max(palindromo(i+1,j), palindromo(i,j-1)) si pal[i] != pal[j]
 
 COSTE
    O(n^2 + nuevaPalabra) tanto en tiempo como en espacio, siendo n el número de letras de la palabra original.
*/


std::string resuelve(std::string const& word) {
    int n = word.length();
    Matriz<int> palindromos(n + 1, n + 1, 0);
    
    for (int i = 1; i <= n; ++i)
        palindromos[i][i] = 1;
    
    for (int d = 1; d <= n - 1; ++d) { // recorre diagonales
        for (int i = 1; i <= n - d; ++i) { // recorre elementos de diagonal
            int j = i + d;
            if (word[i-1] == word[j-1])
                palindromos[i][j] = palindromos[i + 1][j - 1] + 2;
            else
                palindromos[i][j] = std::max(palindromos[i + 1][j], palindromos[i][j - 1]);
        }
    }
    
    int max = palindromos[1][n];
    std::string resultado(max, '\0');
    
    int j = n, i = 1, iRes = 0, jRes = max - 1;
    while (max >= 0) {
        if (word[i-1] == word[j-1]) {
            resultado[iRes] = word[i-1];
            resultado[jRes] = word[j-1];
            ++i; ++iRes;
            --j; --jRes;
            max -= 2;
        }
        else if (max == 0) {
            resultado[iRes] = word[j-1];
            --max;
        } else if (word[i-1] != word[j-1]) {
            if (palindromos[i][j - 1] <= palindromos[i + 1][j])
                ++i;
            else
                --j;
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
