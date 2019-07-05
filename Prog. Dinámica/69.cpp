//TAIS57
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Matriz.h"

/*
Problema 69 🌚
 
 peliculas(i,j) = máximo de minutos que puedo ver con las peliculas de i a N, sabiendo que la ultima pelicula que he visto he terminado de verla a la hora j.
 
 Caso base:
    pelicula(0,j) = 0
 
 Caso recursivo:
     peliculas(i, j) = peliculas(i - 1, j) si pelicula[i].inicio > j
     peliculas(i, j) = max(peliculas(i - 1, j), peliculas(i - 1, j - pelicula[i].fin) + pelicula[i].duracion) si pelicula[i].inicio <= j
 
 Costes:
    O(N * 24 * 60) en tiempo, siendo n el numero de peliculas y el 24 * 60 el numero de minutos del día.
    O(24 * 60) en espacio.
 
 */

struct tPelicula {
    int ini;
    int dur;
    int fin;
    
    tPelicula(int i, int d) : ini(i), dur(d) {
        fin = ini + d + 10;
    };
    
    tPelicula() {};
};

bool operator<(const tPelicula &t1, const tPelicula &t2){
    return t1.ini < t2.ini;
}

int resuelve (const std::vector<tPelicula> &v) {
    int N = v.size(), M = (24 * 60) + 10; //M es conversión de horas a minutos.
    
    std::vector<int> peliculas(M + 1, 0);
    
    for (int i = N; i >= 1; --i) {
        for (int j = 0; j <= M - 10; ++j) {
            if (v[i-1].ini >= j && v[i-1].fin <= M)
                peliculas[j] = std::max(peliculas[j], peliculas[v[i - 1].fin] + v[i - 1].dur);
        }
    }
    
    return peliculas[0];
}

bool resuelveCaso() {
    
    int N;
    std::cin >> N;
    
    if (N == 0) return false;
    
    std::vector<tPelicula> listaPelis;
    
    tPelicula tmp;
    
    for (int i = 0; i < N; ++i) {
        int iniH, iniM, d;
        char aux;
        std::cin >> iniH >> aux >> iniM >> d;
        listaPelis.push_back({ iniH * 60 + iniM, d});
    }
    
    std::sort(listaPelis.begin(), listaPelis.end());
    
    std::cout << resuelve(listaPelis) << "\n";
    
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
