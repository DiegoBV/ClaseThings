#include <string>
#include <vector>
#include <iostream>
using namespace std;


const vector <int> valor = { 1, 2, 5, 10, 20, 50, 100, 200 };
vector <bool> marcador; //esto de aqui deberia pasar por referencia o nos corta la cabeza pero me daba pereza -_-

int sumaValores(vector <int> &v, int k, int &suma) {
	int aux;
	aux = suma + (v[k] * valor[k]);
	return aux;
}

bool es_solucion(int precio, int suma, int pos) {
	return (suma == precio) && !marcador[pos];
}

bool es_completable(int precio, int suma, int pos) {
	return (suma < precio) && !marcador[pos];
}

void procesaSolucion(int cantidad, bool &finish) {
	cout << cantidad << endl;
	finish = true;
	for (int i = 0; i < marcador.size(); i++) {
		if (marcador[i]) {
			cout << "Moneda de " << valor[i] << " centimos" << endl; //para debuguear
		}
	}
}


void quita_calderilla(vector <int> &v, int k, int precio, int suma, int cantidad, bool &finish) {
	if (suma < precio) {
		int i = k + 1;

		while (i < v.size() && !finish)
		{
			int sumaTemporal = sumaValores(v, i, suma);
			if (es_solucion(precio, sumaTemporal, i)) {
				marcador[i] = true;
				procesaSolucion(cantidad + v[i], finish);
			}
			else if (es_completable(precio, sumaTemporal, i)) {
				marcador[i] = true;
				quita_calderilla(v, k + 1, precio, sumaTemporal, cantidad + v[i], finish);
				marcador[i] = false;
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
	marcador.resize(valor.size());

	while (i < n) {
		int suma = 0;
		int cantidad = 0;
		bool finish = false;
		int precio;

		cin >> precio;
		if (precio == 0) {
			cout << 0 << endl;
		}
		else {
			rellena_Vector(calderilla);
			quita_calderilla(calderilla, -1, precio, suma, cantidad, finish);
			if (!finish) {
				cout << "IMPOSIBLE" << endl;
			}
		}
		for (int i = 0; i < marcador.size(); i++) {
			marcador[i] = false;
		}
		i++;
	}
	return 0;
}