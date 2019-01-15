#include <fstream>
#include <iostream>
#include <vector>

#include "PriorityQueue.h"

struct Tarea {
    unsigned int inicio;
    unsigned int fin;
    unsigned int repe;
    Tarea() : inicio(0), fin(0), repe(0) {}
    Tarea(const int &i, const int &f, const unsigned int &r)
    : inicio(i), fin(f), repe(r) {};
};

class ListaTareas {
    
private:
    
    class Comparador {
    public:
        bool operator()(Tarea t1, Tarea t2) {
            return t1.inicio < t2.inicio;
        }
    };
    
    PriorityQueue<Tarea, Comparador> cola;
    
public:
    
    void insertar(const int &i, const int &f,
                  const unsigned int &r) {
        Tarea p(i, f, r);
        cola.push(p);
    }
    
    bool empty() const {
        return cola.empty();
    }
    
    
    Tarea top() const {
        return cola.top();
    }
    
    void pop() {
        cola.pop();
    }
};

bool resuleveCaso() {
    bool solapa = false;
    unsigned int tareasUnicas, tareasPeriodicas;
    unsigned int minutos, m = 0, ocupacion = 0;
    
    std::cin >> tareasUnicas;
    if (!std::cin) return false;
    
    ListaTareas tareas;
    
    std::cin >> tareasPeriodicas >> minutos;
    
    for (int i = 0; i < tareasUnicas; ++i) {
        unsigned int ini, fin;
        std::cin >> ini >> fin;
        tareas.insertar(ini, fin, 0);
    }
    
    for (int i = 0; i < tareasPeriodicas; ++i) {
        unsigned int ini, fin, repe;
        std::cin >> ini >> fin >> repe;
        tareas.insertar(ini, fin, repe);
    }
    
    while (!tareas.empty() && !solapa && m < minutos) {
        Tarea tarea = tareas.top(); tareas.pop();
            
        if ((tarea.inicio < ocupacion) || (!tareas.empty() && tarea.inicio != minutos && tarea.inicio == tareas.top().inicio)) solapa = true;
        else {
            ocupacion = tarea.fin;
            if (tarea.repe > 0) tareas.insertar(tarea.inicio+tarea.repe, tarea.fin+tarea.repe,tarea.repe);
            m = tarea.fin;
        }
    }
    
    if (!solapa) std::cout << "NO\n";
    else std::cout << "SI\n";
    
    return true;
}

int main() {// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuleveCaso());
    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    return 0;
}
