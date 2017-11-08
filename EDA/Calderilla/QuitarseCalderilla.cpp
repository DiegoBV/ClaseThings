#include <string>
#include <vector>
#include <iostream>
using namespace std;


const vector <int> valor = { 1, 2, 5, 10, 20, 50, 100, 200 };
int cant_Max = 0;

bool es_solucion(const int precio, const int suma) {
	return (suma == precio);
}

bool es_completable(const int precio, const vector <int> &sol, const int k, const int suma) {
	return (k < sol.size() && suma < precio);
}

void procesaSolucion(int cantidad) {
	if (cantidad > cant_Max) {
		cant_Max = cantidad;
	}
}

bool es_Prometedora(const int precio, const int suma, const int cantidad, const int k) {
	int cantRestante = precio - suma;
	int pos = 0;
	if (k + 1 == valor.size()) {
		pos = k;
	}
	else {
		pos = k + 1;
	}
	if ((cantidad + cantRestante / valor[pos]) < cant_Max) {
		return false;
	}
	else {
		return true;
	}
}

void quita_calderilla(const vector <int> &v, vector <int> &sol, int k, const int precio, int suma, int cantidad) {
	int i = 0;
	while (k < v.size() && i <= v[k])
	{
		sol[k] = i;
		if (es_solucion(precio, suma)) {
			procesaSolucion(cantidad);
		}
		else if (es_completable(precio, sol, k, suma) && es_Prometedora(precio, suma, cantidad, k)) {
			quita_calderilla(v, sol, k + 1, precio, suma, cantidad);
			if (k + 1 < v.size())
				sol[k + 1] = 0;  //reinicia el elemento posterior
		}
		i++;
		cantidad++;
		suma += valor[k];
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
		int precio;
		cin >> precio;
		rellena_Vector(calderilla);
		quita_calderilla(calderilla, sol, 0, precio, 0, 0);
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