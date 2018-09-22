#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "Pacientes.h"



void resuleveCaso() {
    
    int n;
    std::string nombre;
    unsigned int gravedad;
    char estado;
    
    std::cin >> n;
    
    while (n != 0) {
        ListaPacientes cola;
        for (unsigned int i = 0; i < n; ++i) {
            std::cin >> estado;
            if (estado == 'I') {
                std::cin >> nombre >> gravedad;
                cola.insertar(nombre, gravedad);
            } else if (estado == 'A') {
                std::cout << cola.primerNombre() << '\n';
                cola.pop();
            }
        }
        std::cout << "----\n";
        std::cin >> n;
    }
    
}

int main() {// ajustes para que cin extraiga directamente de un fichero
    /*#ifndef DOMJUDGE
        std::ifstream in("casos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif*/
    
    resuleveCaso();
    
    // para dejar todo como estaba al principio
    /*#ifndef DOMJUDGE
        std::cin.rdbuf(cinbuf);
        //system("PAUSE");
    #endif*/
    return 0;
}
