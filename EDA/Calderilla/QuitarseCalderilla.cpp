#include <string>
#include <vector>
#include <iostream>
using namespace std;


const vector <int> valor = { 1, 2, 5, 10, 20, 50, 100, 200 };

int sumaValores(vector <int> &v, int k, int &suma, int &cantidad) {
	int aux;
	aux = suma + (v[k] * valor[k]);
	return aux;
}

bool es_solucion(int precio, int suma) {
	return (suma == precio);
}

bool es_completable(int precio, int &suma, int &cantidad, int k) {
	return (suma < precio);
}

void procesaSolucion(int cantidad, bool &finish) {
	cout << cantidad << endl;
	finish = true;
}

void quita_calderilla(vector <int> &v, int k, int precio, int suma, int cantidad, bool &finish) {
	if (suma < precio) {
		int i = k;

		while (i < v.size() && !finish)
		{
			int sumaTemporal = sumaValores(v, i, suma, cantidad);
			if (es_solucion(precio, sumaTemporal)) {
				procesaSolucion(cantidad + v[k], finish);
			}
			else if (es_completable(precio, sumaTemporal, cantidad, k)) {
				quita_calderilla(v, k + 1, precio, sumaTemporal, cantidad + v[k], finish);
			}
			i++;
		}
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

	//Function
	cin >> n;
	calderilla.resize(8);

	while (i < n) {
		int suma = 0;
		int cantidad = 0;
		bool finish = false;
		int precio;

		cin >> precio;
		if (precio == 0) {
			cout << 0;
		}
		else {
			rellena_Vector(calderilla);
			quita_calderilla(calderilla, 0, precio, suma, cantidad, finish);
			if (!finish) {
				cout << "IMPOSIBLE" << endl;
			}
		}
		i++;
	}
	return 0;
}