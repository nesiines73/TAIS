#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

struct Hora {
    int hora;
    int minutos;
};

Hora operator+(Hora const &a, int const &minutos) {
    Hora resultado = a;
    resultado.minutos += minutos;
    while (resultado.minutos >= 60) {
        resultado.minutos -= 60;
        ++resultado.hora;
    }
    return resultado;
}

bool operator<(Hora const &a, Hora const &b) {
    if (a.hora == b.hora) return a.minutos < b.minutos;
    return (a.hora < b.hora);
}

bool operator<=(Hora const &a, Hora const &b) {
    if (a.hora == b.hora) return a.minutos <= b.minutos;
    return (a.hora <= b.hora);
}

bool operator==(Hora const &a, Hora const &b) {
    return a.hora == b.hora && a.minutos == b.minutos;
}

struct Pelicula {
    Hora inicio;
    Hora fin;
    
    bool operator<(const Pelicula& p) const {
        return fin < p.fin;
    }
    
    bool operator<=(const Pelicula& p) const {
        return fin <= p.fin;
    }
};


void descanso(Hora &h) {
    h.minutos += 10;
    if (h.minutos >= 60) {
        h.minutos -= 60;
        ++h.hora;
    }
}

void resuelveCaso(int numCasos) {
    Pelicula p;
    Hora h;
    int minutos;
    char aux;
    std::vector<Pelicula> cartelera;
    
    for (int i = 0; i < numCasos; ++i) {
        std::cin >> h.hora >> aux >> h.minutos >> minutos;
        p.inicio = h;
        p.fin = h + minutos;
        cartelera.push_back(p);
    }
    
    std::sort(cartelera.begin(), cartelera.end());
    
    int maxPeliculas = 1;
    Hora t = cartelera[0].fin;
    descanso(t);
    for (int i = 1; i < cartelera.size(); ++i) {
        if (t <= cartelera[i].inicio) {
            ++maxPeliculas;
            t = cartelera[i].fin;
            descanso(t);
        }
    }
    
    std::cout << maxPeliculas << "\n";
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    int casos = 0;
    std::cin >> casos;
    while (casos != 0) {
        resuelveCaso(casos);
        std::cin >> casos;
    }
    
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
