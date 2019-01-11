#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include "Matriz.h"

const int INF = 1e9;

int monedas(const std::vector<int> &valor, const std::vector<int> &cantidad, const int &precio) {
   
    Matriz<int> mat(valor.size() + 1, precio + 1, INF);
    
    mat[0][0] = 0;
    
    for (int i = 1; i <= valor.size(); ++i) {
        mat[i][0] = 0;
        for (int j = 1; j <= precio; ++j) {
            mat[i][j] = mat[i - 1][j];
            if (j >= valor[i - 1]) {
                int temp = INF;
                
                for (int k = 1; k <= cantidad[i - 1] && j - k * valor[i - 1] >= 0 && j - k * valor[i - 1] <= precio; ++k) {
                    temp = mat[i - 1][j - k * valor[i - 1]] + k;
                    if (temp < mat[i][j])
                        mat[i][j] = temp;
                }
            }
        }
    }
   
    return mat[valor.size()][precio];
}

bool resuelveCaso() {
    int n, precio;
    std::cin >> n;
    
    if (!std::cin) return false;
    
    std::vector<int> valorMoneda(n), cantidadMonedas(n);
    
    for (int i = 0; i < n; ++i)
        std::cin >> valorMoneda[i];
    
    for (int i = 0; i < n; ++i)
        std::cin >> cantidadMonedas[i];
    
    std::cin >> precio;
    
    int sol = monedas(valorMoneda, cantidadMonedas, precio);
    if (sol == INF)
        std::cout << "NO\n";
    else
        std::cout << "SI " << sol << "\n";
    
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
