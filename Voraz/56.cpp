#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "PriorityQueue.h"

struct Horario {
    int id;
    int horaIni;
    int horaFin;
    
    bool operator<(Horario const &c) const{
        return horaIni < c.horaIni || (horaIni == c.horaIni && horaFin < c.horaFin);
    }

	bool operator>(Horario const &c) const {
		return c.horaFin > horaFin || (horaFin == c.horaFin && c.horaIni > horaIni);
	}
};

void resuelveCaso(int numConf) {
    Horario c;
    std::vector<Horario> v;
    
    for (int i = 0; i < numConf; ++i) {
        std::cin >> c.horaIni >> c.horaFin;
        v.push_back(c);
    }
    
    std::sort(v.begin(), v.end());
    
    PriorityQueue<Horario, std::greater<Horario>> alumnos;
    
    int companhero = 0;
    
    for (int i = 0; i < v.size(); ++i) {
        if (alumnos.empty())
            alumnos.push({ companhero, v[i].horaIni, v[i].horaFin});
        else if (alumnos.top().horaFin <= v[i].horaIni) {
            int id = alumnos.top().id;
            alumnos.pop();
            alumnos.push({ id, v[i].horaIni, v[i].horaFin});
        }
        else if (alumnos.top().horaFin > v[i].horaIni) {
            ++companhero;
            alumnos.push({ companhero, v[i].horaIni, v[i].horaFin});
        }
    }
    
    std::cout << companhero << "\n";
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
