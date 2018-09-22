#ifndef PACIENTES_H
#define PACIENTES_H

#include <string>
#include "PriorityQueue.h"

class ListaPacientes {
    
private:
    struct Paciente{
        std::string nombre;
        int gravedad;
        int ordenLlegada;
        Paciente() : nombre(""), gravedad(0), ordenLlegada(0){}
        Paciente(const std::string &n, const int &g, const int &o) : nombre(n), gravedad(g), ordenLlegada(o){};
    };
    
    class Comparador {
    public:
        bool operator()(Paciente pac1, Paciente pac2) {
            return (pac1.gravedad == pac2.gravedad && pac1.ordenLlegada < pac2.ordenLlegada) ||  pac1.gravedad > pac2.gravedad;
        }
    };
    
    PriorityQueue<Paciente, Comparador> cola;
    int orden;
    
public:
    ListaPacientes() : orden(0){};
    
    void insertar(const std::string &nombre, const int &gravedad){
        Paciente p(nombre, gravedad,orden);
        ++orden;
        cola.push(p);
    }
    
    bool empty() const{
        return cola.empty();
    }
    
    std::string primerNombre() const{
        return cola.top().nombre;
    }
    
    void pop() {
        cola.pop();
    }
};

#endif //PACIENTES_H
