#include <string>
#include <vector>
#include <iostream>
using namespace std;


const vector <int> valor = { 1, 2, 5, 10, 20, 50, 100, 200 };
int cant_Max = 0;

int sumaValores(const vector <int> &sol, const int k) {
	int sumaTotal = 0;
	for (int i = 0; i < sol.size(); i++) {
		sumaTotal += sol[i] * valor[i];
	}

	return sumaTotal;
}

bool es_solucion(const int precio, const vector <int> &sol) {
	return (sumaValores(sol, sol.size()) == precio);
}

bool es_completable(const int precio, const vector <int> &sol, const int k) {
	return (k < sol.size() && sumaValores(sol, k) < precio);
}

void procesaSolucion(const vector <int> &sol) {
	int cantidad = 0;
	for (int i = 0; i < sol.size(); i++) {
		cantidad += sol[i];
	}
	if (cantidad > cant_Max) {
		cant_Max = cantidad;
	}
}


void quita_calderilla(const vector <int> &v, vector <int> &sol, int k, const int precio) {
	int i = 0;
	if (k < v.size() && v[k] == 0) {
		quita_calderilla(v, sol, k + 1, precio);
		if (k + 1 < v.size())
			sol[k + 1] = 0; //reinicia el elemento posterior
	}
	else {
		while (k < v.size() && sol[k] < v[k])
		{
			sol[k]++;
			if (es_solucion(precio, sol)) {
				procesaSolucion(sol);
			}
			else if (es_completable(precio, sol, k)) {
				quita_calderilla(v, sol, k + 1, precio);
				if (k + 1 < v.size())
					sol[k + 1] = 0;  //reinicia el elemento posterior
			}
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
	calderilla.resize(8);

	//Function
	cin >> n;

	while (i < n) {
		vector <int> sol;
		sol.resize(8);
		for (int i = 0; i < sol.size(); i++) {
			sol[i] = 0;
		}
		int precio;
		cin >> precio;
		rellena_Vector(calderilla);
		quita_calderilla(calderilla, sol, 0, precio);

		if (cant_Max == 0) {
			cout << "IMPOSIBLE" << endl;
		}
		else {
			cout << cant_Max << endl;
		}

		cant_Max = 0;
		i++;
	}
	return 0;
}