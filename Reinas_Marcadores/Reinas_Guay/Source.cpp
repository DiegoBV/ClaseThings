//Grupo 22 Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción de la solución:
/*
	Después de introducir el numero de casos de prueba que queremos considerar y el número N de reinas en un tablero de NxN, se 
	invoca a la función Cuatro_Reinas(...). Dicha función comprueba todo el árbol de soluciones parciales, descartando las que
	son inválidas bien por que la reina en cuestión está en la misma columna o bien por estar en la misma diagonal, usando 
	los métodos auxiliares para ello. Para hacerlo más eficiente, hacemos uso de marcadores en las diagonales y en las horizontales.
*/
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

		for (v[fila] = 0; v[fila] < n; v[fila]++) { //coloca la reina en la posicion 0, 1, 2, ... N - 1

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
	return (posicion_Vector == (n - 1) && !no_Peligro(v, d_des, d_asc, hilera, posicion_Vector)); //es solucion si es la ultima reina por colocar y 
	//si no hay peligro de comerse
}

bool es_Completable(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector, int n) {
	return (posicion_Vector < (n - 1) && !no_Peligro(v, d_des, d_asc, hilera, posicion_Vector)); //es compeltable si aun quedan reinas por colocar y
	// si no hay peligro de comerse
}

bool no_Peligro(const vector<int> &v, vector<bool> &d_des, vector<bool> &d_asc, vector<bool> &hilera, int posicion_Vector) {
	bool danger = false;
	if (hilera[v[posicion_Vector]]) { //se comprueba que esa posicion no haya sido ocupada antes
		danger = true;
	}
	else if (d_asc[diagonal_Ascendente(posicion_Vector, v[posicion_Vector])]) { //se comprueban las diagonales
		danger = true;
	}
	else if (d_des[diagonal_Descendente(posicion_Vector, v[posicion_Vector], d_des.size())]) {
		danger = true;
	}
	return danger;
}

void procesa_Solucion(int &cont) {
	cont++; //aumenta el contador de soluciones que ha encontrado
}
int diagonal_Descendente(int x, int y, int tam) {
	if ((x - y) < 0) {
		return tam + (x - y); //cambios para los numeros negativos
	}
	else {
		return x - y;
	}
}

int diagonal_Ascendente(int x, int y) {
	return x + y;
}
int main() {
	int m; //petición de datos y mostrar la solución
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