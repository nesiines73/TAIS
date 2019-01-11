#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Matriz.h"
using namespace std;

const int INF = 1e9;

int calcularCaminos(std::vector<string> const& v, int filas, int columnas) {

	Matriz<int> matriz(filas + 1, columnas + 1, 0);

	//int sol = 0;
	matriz[0][1] = 1;
	// rellenar la matriz

	for (int i = 1; i <= filas; ++i) {
		for (int j = 1; j <= columnas; ++j) {
			if (v[i - 1][j - 1] == 'P')
				matriz[i][j] = INF;
			else if (matriz[i-1][j] == INF && matriz[i][j - 1] != INF)
				matriz[i][j] = matriz[i][j - 1];
			else if ( matriz[i][j - 1] == INF && matriz[i-1][j] != INF)
                matriz[i][j] = matriz[i-1][j];
            else if (matriz[i][j - 1] != INF && matriz[i-1][j] != INF)
                matriz[i][j] = matriz[i-1][j] + matriz[i][j - 1];
		}
	}
	return matriz[filas][columnas];
}

bool resuelveCaso() {
   
   // leemos la entrada
   int N, M;
   cin >> N >> M;
   if (!cin)
      return false;
   
   // leemos el mapa
   vector<string> mapa(N);
   for (string & x : mapa) {
      cin >> x;
   }
   
   // resolvemos
   std::cout << calcularCaminos(mapa, N, M) << "\n";
   

   return true;
   
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

   // Resolvemos
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   //system("PAUSE");
#endif
   return 0;
}
