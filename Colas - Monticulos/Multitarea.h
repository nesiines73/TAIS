#ifndef MULTITAREA_H
#define MULTITAREA_H

#include "PriorityQueue.h"

class ListaTareas {

private:
	struct Tarea {
		char tipo;
		unsigned int inicio;
		unsigned int fin;
		unsigned long long int minutos;
		unsigned long long int repe;
		Tarea() : tipo(), inicio(0), fin(0), minutos(0), repe(0) {}
		Tarea(const char &n, const int &i, const int &f, const unsigned long long int &m, const unsigned long long int &r) 
			: tipo(n), inicio(i), fin(f), minutos(m), repe(r) {};
	};

	class Comparador {
	public:
		bool operator()(Tarea t1, Tarea t2) {
			return t1.inicio == t2.inicio || t1.fin == t2.fin;
		}
	};

	PriorityQueue<Tarea, Comparador> cola;
	int orden;

public:
	ListaTareas() : orden(0) {};

	void insertar(const char &tipo, const int &i, const int &f, const unsigned long long int &m,
		const unsigned long long int &r) {
		Tarea p(tipo, i, f, m, r);
		++orden;
		cola.push(p);
	}

	bool empty() const {
		return cola.empty();
	}

	unsigned int primerInicio() const {
		return cola.top().inicio;
	}

	/*char tipo() const {
		return cola.top().tipo;
	}*/

	void pop() {
		if (cola.top().tipo == 'P') {
			Tarea aux = cola.top();
			cola.pop();
			cola.push(aux);
		}
		else 
			cola.pop();
	}
};

#endif //PACIENTES_H