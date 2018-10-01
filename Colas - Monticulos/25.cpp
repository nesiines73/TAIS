#include <fstream>
#include <iostream>
#include <vector>

#include "PriorityQueue.h"

class OrquestaAnInMus {
public:
    struct musicosPartituras{
        unsigned int musico;
        unsigned int partitura;
    };
    bool operator() (const musicosPartituras &mP1, const musicosPartituras &mP2) const {
        unsigned int musicos1, musicos2;
        
        musicos1 = mP1.musico / mP1.partitura;
        if (mP1.musico % mP1.partitura != 0)
            musicos1++;
        
        musicos2 = mP2.musico / mP2.partitura;
        if(mP2.musico % mP2.partitura != 0)
            musicos2++;
        
        return musicos1 > musicos2;
    }
};

//Coste O(logn)
bool resuelveCaso(){
    unsigned int partituras, instrumentos, musicos, resultado;
    std::cin >> partituras;
    
    if (!std::cin)  return false;
    
    std::cin >> instrumentos;
    
    PriorityQueue<OrquestaAnInMus::musicosPartituras,OrquestaAnInMus> pq;
    OrquestaAnInMus::musicosPartituras mp;
    
    mp.partitura = 1;
    for (unsigned int i = 0; i < instrumentos; ++i){
        std::cin >> musicos;
        mp.musico = musicos;
        pq.push(mp);
    }
    
    partituras = partituras - pq.size();
    
    while (partituras > 0){
        mp = pq.top();
        pq.pop();
        mp.partitura++;
        pq.push(mp);
        partituras--;
    }
    mp = pq.top();
    resultado = mp.musico / mp.partitura;
    
    if (mp.musico % mp.partitura != 0) resultado++;
    std::cout << resultado << '\n';
    
    return true;
}

int main() {// ajustes para que cin extraiga directamente de un fichero
	#ifndef DOMJUDGE
        std::ifstream in("casos.txt");
        auto cinbuf = std::cin.rdbuf(in.rdbuf());
    #endif
    
    while(resuelveCaso());
    // para dejar todo como estaba al principio
    #ifndef DOMJUDGE
        std::cin.rdbuf(cinbuf);
        //system("PAUSE");
    #endif
    return 0;
}
