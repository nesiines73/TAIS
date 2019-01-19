#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Intervalo {
    int ini;
    int fin;
        
    bool operator<(Intervalo const &i) const {
        return ini < i.ini;
    }
    
    bool operator<=(Intervalo const &i) const {
        return ini <= i.ini;
    }
};

bool resuelveCaso() {
    int C, F, N;
    std::cin >> C >> F >> N;
    
    if (C == 0 && F == 0 && N == 0) return false;
    
    Intervalo aux;
    std::vector<Intervalo> v(N);
    
    for (int c = 0; c < N; ++c) {
        std::cin >> aux.ini >> aux.fin;
        v[c] = aux;
    }
    
    std::sort(v.begin(), v.end());
    
    bool completado = false, hueco = false;
    int fin = C, finCandidato = -1;
    int trabajos = 0;
    
    for (int i = 0; i < N && !hueco && !completado; ++i) {
        if(v[i].ini <= fin && v[i].fin > fin) {
            if(v[i].fin > finCandidato)
                finCandidato = v[i].fin;
        }
        else if(v[i].ini > fin && !hueco) {
            ++trabajos;
            fin = finCandidato;
            if(fin >= F)
                completado = true;
            
            else{
                if(v[i].ini > fin)
                    hueco = true;
                
                else if(v[i].ini <= fin && v[i].fin > fin) {
                    if(v[i].fin > finCandidato)
                        finCandidato = v[i].fin;
                }
            }
        }
    }
    
    if(!hueco && (finCandidato != fin)) {
        ++trabajos;
        fin = finCandidato;
    }
    
    if(fin < F) hueco = true;
    

    if (hueco) std::cout << "Imposible\n";
    else std::cout << trabajos << "\n";
    
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
