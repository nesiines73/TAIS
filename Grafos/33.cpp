#include <iostream>
#include <fstream>
#include <vector>

template <typename Object>
class Matriz {
public:
    Matriz(size_t fils, size_t cols, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}
    
    std::vector<Object> const& operator[](size_t f) const {
        return datos[f];
    }
    std::vector<Object> & operator[](size_t f) {
        return datos[f];
    }
    
    Object const& at(size_t f, size_t c) const {
        return datos.at(f).at(c);
    }
    
    Object & at(size_t f, size_t c) {
        return datos.at(f).at(c);
    }
    
    size_t numfils() const { return datos.size(); }
    size_t numcols() const { return numfils() > 0 ? datos[0].size() : 0; }
    
    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }
    
private:
    std::vector<std::vector<Object>> datos;
};

class BuscaOvejas{
public:
    BuscaOvejas() :count(0) {}
private:
    std::vector<int> id;
    int count;
};

struct Casilla {
    int fila;
    int col;
};

std::vector<Casilla> casillasAdyacentes(Matriz<char> const &m, Casilla const &c) {
    std::vector<Casilla> vectorCasillasAdy;
    Casilla casillaAdy;
    int rowAux, colAux;
    for (int i = 0; i < 4; ++i) {
        switch (i) {
            case 0:
                rowAux = -1;
                colAux = 0;
                break;
            case 1:
                rowAux = 0;
                colAux = 1;
                break;
            case 2:
                rowAux = 1;
                colAux = 0;
                break;
            case 3:
                rowAux = 0;
                colAux = -1;
                break;
        }
        casillaAdy.fila = c.fila + rowAux;
        casillaAdy.col = c.col + colAux;
        if (casillaAdy.fila >= 0 && casillaAdy.fila < m.numfils() &&
            casillaAdy.col >= 0 && casillaAdy.col < m.numcols()) {
            if (m[casillaAdy.fila][casillaAdy.col] == '.')
                vectorCasillasAdy.push_back(casillaAdy);
        }
    }
    return vectorCasillasAdy;
}

void cuentaOvejasRecursivo(Matriz<char> const & m, Matriz<bool> &marcado, Casilla const & c, int &contador) {
    marcado[c.fila][c.col] = true;
    for (auto w : casillasAdyacentes(m, c)) {
        if (!marcado[w.fila][w.col])
            cuentaOvejasRecursivo(m, marcado, w, contador);
    }
}

int cuentaOvejasBlancas(Matriz<char> const & m, Matriz<bool> &marcado) {
    Casilla c;
    int contador = 0;
    for (int i = 0; i < m.numfils(); ++i) {
        c.fila = i;
        for (int j = 0; j < m.numcols(); ++j) {
            c.col = j;
            if (!marcado[i][j]) {
                cuentaOvejasRecursivo(m, marcado, c, contador);
                ++contador;
            }
        }
    }
    return contador - 1;
}

bool resuelveCaso() {
    int ancho, alto;
    std::cin >> ancho >> alto;
    if (!std::cin) return false;
    
    Matriz<char> m(alto, ancho, '.');
    Matriz<bool> marcado(alto, ancho, false);
    char elem;
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            std::cin >> elem;
            if (elem == 'X') marcado[i][j] = true;
            m[i][j] = elem;
        }
    }
    
    std::cout << cuentaOvejasBlancas(m, marcado) << "\n";
    
    return true;
}

int main(){
    
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
    
    while (resuelveCaso());
    
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    //system("PAUSE");
#endif
    
    return 0;
}
