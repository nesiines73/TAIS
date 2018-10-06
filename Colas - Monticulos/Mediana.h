#ifndef COLAMEDIANAS_H
#define COLAMEDIANAS_H

#include "PriorityQueue.h"

template <class T>
class ColaMedianas {
    
public:
    ColaMedianas() : _colamin(), _colamax() {}
    
    ~ColaMedianas() {}
    
    void push(const int& x) {
        if (_colamax.empty()) _colamax.push(x);
        else { // en caso contrario, se introduce en un monticulo u otro
            if (x > _colamax.top()) _colamax.push(x);
            else _colamin.push(x);
            recolocar();
        }
        
    }
    
    int mediana() const {
        if (!_colamax.empty() && !_colamin.empty() && (_colamax.size() + _colamin.size()) %2 == 0) //Para los pares
            return _colamax.top() + _colamin.top();
        
        return _colamax.top() * 2; //Impares
    }
    
    void pop() {
        _colamax.pop();
        recolocar();
    }
    
private:
    
    PriorityQueue<int, std::greater<int>> _colamin;
    PriorityQueue<int, std::less<int>> _colamax;
    
    void recolocar() {
        if (_colamax.size() == (_colamin.size() + 2)) {
            _colamin.push(_colamax.top());
            _colamax.pop();
        }
        else if (_colamin.size() == (_colamax.size() + 1)) {
            _colamax.push(_colamin.top());
            _colamin.pop();
        }
        
    }
};

#endif
