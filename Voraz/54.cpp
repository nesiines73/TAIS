#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Edificio {
    int oeste;
    int este;
};

bool operator<(const Edificio &a, const Edificio &b) {
    if (a.oeste == b.oeste)
        return (a.este - a.oeste) < (b.este - b.oeste);
    else
        return a.oeste < b.oeste;
}


int pasadizos(const std::vector<Edificio> &ed) {
    
    int nPas = 1, primerFin = ed[0].este;
    
    for (int i = 0; i < ed.size() - 1; i++) {
        if (ed[i + 1].oeste < primerFin) {
            if (primerFin > ed[i + 1].este)
                primerFin = ed[i + 1].este;
        }
        else {
            nPas++;
            primerFin = ed[i + 1].este;
        }
    }
    
    return nPas;
}


bool resuelveCaso() {
    
    int n;
    std::cin >> n;
    
    if (n == 0) return false;
    
    std::vector<Edificio> edificios(n);
    
    for (int i = 0; i < n; ++i)
        std::cin >> edificios[i].oeste >> edificios[i].este;
        
    std::sort(edificios.begin(), edificios.end());
    std::cout << pasadizos(edificios) << "\n";
    
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
