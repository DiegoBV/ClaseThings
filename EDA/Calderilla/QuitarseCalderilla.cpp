#include <string>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

bool es_solucion(const int &precio, const int &suma) {
	return (suma == precio);
}

bool es_completable(const int &precio, const vector <int> &v, const int &k, const int &suma) {
	return (k < v.size() && suma < precio);
}

void procesaSolucion(const int &cantidad, int &cant_Max) {
	if (cantidad > cant_Max) {
		cant_Max = cantidad;
	}
}

bool es_Prometedora(const int &precio, const int &suma, const int &cantidad, const int &k, const vector <int> &valor, const int cant_Max) {
	/*int cantRestante = precio - suma;
	int pos;
	if (k + 1 == valor.size()) {
	pos = k;
	}
	else {
	pos = k + 1;
	}
	if ((cantidad + (int)(cantRestante/valor[pos])) < cant_Max) {
	return false;
	}
	else {
	return true;
	}*/
	return ((precio - suma + cantidad) > cant_Max);
}
//Coste = x1 * x2 * x3... * x8, siendo xn el numero de monedas en dicha posicion
void quita_calderilla(const vector <int> &v, int k, const int &precio, int suma, int cantidad, const vector <int> &valor, int &cant_Max) {
	int i = 0;
	bool cont = true;
	while (k < v.size() && i <= v[k] && cont)
	{
		int sumaAux = suma + i * valor[k];
		int cantAux = cantidad++;
		if (es_solucion(precio, sumaAux)) {
			procesaSolucion(cantAux, cant_Max);
			cont = false;
		}
		else if (es_completable(precio, v, k, sumaAux) && es_Prometedora(precio, sumaAux, cantAux, k, valor, cant_Max)) {
			quita_calderilla(v, k + 1, precio, sumaAux, cantAux, valor, cant_Max);
		}
		else {
			cont = false;
		}
		i++;
	}
}



void rellena_Vector(vector <int> &v) {
	for (int i = 0; i < v.size(); i++) {
		cin >> v[i];
	}
}


int main() {
	//Atributes
	int n;
	int i = 0;
	vector <int> calderilla;
	calderilla.resize(8);
	const vector <int> valor = { 1, 2, 5, 10, 20, 50, 100, 200 };
	int cant_Max = -1;

	//Function
	cin >> n;

	while (i < n) {
		int precio;
		cin >> precio;
		rellena_Vector(calderilla);
		quita_calderilla(calderilla, 0, precio, 0, 0, valor, cant_Max);
		if (cant_Max == -1) {
			cout << "IMPOSIBLE" << endl;
		}
		else {
			cout << cant_Max << endl;
		}
		cant_Max = -1;
		i++;
	}
	return 0;
}