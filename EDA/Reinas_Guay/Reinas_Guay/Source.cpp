#include <iostream>
#include <vector>
#include <string>
using namespace std;




void Cuatro_Reinas(vector<int> &v, int fila, int n, int &cont);
bool es_Solucion(const vector<int> &v, int posicion_Vector, int n);
bool es_Completable(const vector<int> &v, int posicion_Vector, int n);
bool no_Peligro(const vector<int> &v, int posicion_Vector);
int diagonal_Ascendente(int x, int y);
int diagonal_Descendente(int x, int y);
void procesa_Solucion(int &cont);

void Cuatro_Reinas(vector<int> &v, int fila, int n, int &cont) {  

	if (fila < n) {

		for (v[fila] = 0; v[fila] < n; v[fila]++) {

			if (es_Solucion(v, fila, n)) {
				procesa_Solucion(cont);
			}
			else if (es_Completable(v, fila, n)) {
				Cuatro_Reinas(v, fila + 1, n, cont);
			}
		}
	}
}

bool es_Solucion(const vector<int> &v, int posicion_Vector, int n) {

	if (posicion_Vector == (n - 1) && !no_Peligro(v, posicion_Vector)) {
		return true;
	}
	else
		return false;
}

bool es_Completable(const vector<int> &v, int posicion_Vector, int n) {

	if (posicion_Vector < (n - 1) && !no_Peligro(v, posicion_Vector)) {
		return true;
	}
	else
		return false;
}

bool no_Peligro(const vector<int> &v, int posicion_Vector) {
	bool danger = false;
	int i = 0;

	while (!danger && i < posicion_Vector) {
		if (v[i] == v[posicion_Vector]) {  //misma columna
			danger = true;
		}
		else if (diagonal_Descendente(i, v[i]) == diagonal_Descendente(posicion_Vector, v[posicion_Vector])) {
			danger = true;
		}
		else if (diagonal_Ascendente(i, v[i]) == diagonal_Ascendente(posicion_Vector, v[posicion_Vector])) {
			danger = true;
		}
		i++;
	}

	return danger;
}

void procesa_Solucion(int &cont) {
		 cont++;
}
int diagonal_Descendente(int x, int y) {
	return x - y;
}

int diagonal_Ascendente(int x, int y) {
	return x + y;
}


int main() {
	int m;
	cin >> m;
	int i = 0;
	while (i < m) {
		int cont = 0;
		int n;
		cin >> n;
		vector <int> v;
		v.resize(n);
		Cuatro_Reinas(v, 0, n, cont);
		cout << cont << endl;
		i++;
	}
	return 0;
}