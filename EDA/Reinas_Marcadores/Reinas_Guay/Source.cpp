#include <iostream>
#include <vector>
#include <string>
using namespace std;




void Cuatro_Reinas(vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int fila, int n, int &cont);
bool es_Solucion(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector, int n);
bool es_Completable(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector, int n);
bool no_Peligro(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector);
int diagonal_Ascendente(int x, int y);
int diagonal_Descendente(int x, int y, int tam);
void procesa_Solucion(int &cont);


//Coste O(n!), donde n es el número de Reinas y el tamaño del tablero
//Como queremos encontrar todas las soluciones, el algoritmo debe recorrer el árbol entero y sus posibilidades
void Cuatro_Reinas(vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int fila, int n, int &cont) {

	if (fila < n) {

		for (v[fila] = 0; v[fila] < n; v[fila]++) {

			if (es_Solucion(v, d_des, d_asc, hilera, fila, n)) {
				procesa_Solucion(cont);
			}
			else if (es_Completable(v, d_des, d_asc, hilera, fila, n)) {
				hilera[v[fila]] = true;
				d_des[diagonal_Descendente(fila, v[fila], d_des.size())] = true;        //Si es completable, marcamos sus diagonales y su hilera como false
				d_asc[diagonal_Ascendente(fila, v[fila])] = true;
				Cuatro_Reinas(v, d_des, d_asc, hilera, fila + 1, n, cont);
				hilera[v[fila]] = false;
				d_des[diagonal_Descendente(fila, v[fila], d_des.size())] = false;          // desmarcamos en caso de que haya "Vuelta atrás"
				d_asc[diagonal_Ascendente(fila, v[fila])] = false;
			}
		}
	}
}

bool es_Solucion(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector, int n) {

	if (posicion_Vector == (n - 1) && !no_Peligro(v, d_des, d_asc, hilera, posicion_Vector)) {
		return true;
	}
	else
		return false;
}

bool es_Completable(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector, int n) {

	if (posicion_Vector < (n - 1) && !no_Peligro(v, d_des, d_asc, hilera, posicion_Vector)) {
		return true;
	}
	else
		return false;
}

bool no_Peligro(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector) {
	bool danger = false;
	//int i = 0;
	if (hilera[v[posicion_Vector]]) { //se comprueba que esa posicion no haya sido ocupada antes
		danger = true;
	}
	else if (d_asc[diagonal_Ascendente(posicion_Vector, v[posicion_Vector])]) {
		danger = true;
	}
	else if (d_des[diagonal_Descendente(posicion_Vector, v[posicion_Vector], d_des.size())]) {
		danger = true;
	}
	/*while (!danger && i < posicion_Vector) {
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
	}*/

	return danger;
}

void procesa_Solucion(int &cont) {
	cont++;
}
int diagonal_Descendente(int x, int y, int tam) {
	if ((x - y) < 0) {
		return tam + (x - y);
	}
	else {
		return x - y;
	}
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
		vector <bool> hilera;
		hilera.resize(n);
		vector <bool> d_asc;
		d_asc.resize(n * 2 - 1);
		vector <bool> d_desc;
		d_desc.resize(n * 2 - 1);
		Cuatro_Reinas(v, d_desc, d_asc, hilera, 0, n, cont);
		cout << cont << endl;
		i++;
	}
	return 0;
}