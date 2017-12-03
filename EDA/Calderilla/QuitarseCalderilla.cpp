//Grupo VJ22 Alejandro Marín Pérez y Diego Baratto Valdivia
/*
	El programa recibe un precio y una cantidad de monedas que se tienen. Para buscar la solución más efectiva, es 
	decir, la que da el mayor número de monedas, se explora un árbol de posibilidades usando sólo una moneda, después otra 
	del mismo tipo y así hasta que encuentra una buena solución. Para comprobarlo se usa el es_solución para saber si es posible 
	sea una solución. El propio procesa solución ya comprueba si esa es la mejor solución (cantidad > cant_Max) siendo cant_Max
	la cantidad máxima hasta el momento. SI no es una solución se comprueba si es completable (se puede llegar a una solución) y 
	si esa rama es prometedora (se puede llegar a alcanzar una cantidad mayor que cant_Max) y si no es ese el caso, se vuelve a la
	opción anterior.
*/

#include <string>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

bool es_solucion(const int &precio, const int &suma) {
	return (suma == precio);
}

bool es_completable(const int &precio, const vector <int> &v, const vector <int> &valor, const int &k, const int &suma) {
	return (k < v.size() && suma < precio &&  valor[k] <= precio);
}

void procesaSolucion(const int &cantidad, int &cant_Max) {
	if (cantidad > cant_Max) {
		cant_Max = cantidad;
	}
}

bool es_Prometedora(const int &precio, const int &suma, const int &cantidad, const int &cant_Max) {
	return ((precio - suma + cantidad) > cant_Max);
}

//Coste = x1 * x2 * x3... * x8, siendo xn el numero de monedas en dicha posicion
void quita_calderilla(const vector <int> &v, int k, const int &precio, int suma, int cantidad, const vector <int> &valor, int &cant_Max) {
	int i = 0;
	while (i <= v[k])
	{
		if (i > 0) {
			cantidad++;
			suma += valor[k];
		}
		if (es_solucion(precio, suma)) {
			procesaSolucion(cantidad, cant_Max);
		}
		else if (es_completable(precio, v, valor, k + 1, suma) && es_Prometedora(precio, suma, cantidad, cant_Max)) {
			quita_calderilla(v, k + 1, precio, suma, cantidad, valor, cant_Max);
		}
		i++;
	}
}


void rellena_Vector(vector <int> &v) {
	for (int i = 0; i < v.size(); i++) {
		cin >> v[i];
	}
}

void compruebaCant(int &cant_Max) {
	if (cant_Max == -1) {
		cout << "IMPOSIBLE" << endl;
	}
	else {
		cout << cant_Max << endl;
	}
	cant_Max = -1;
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
		if (precio == 0) {
			cout << 0 << endl;
		}
		else {
			quita_calderilla(calderilla, 0, precio, 0, 0, valor, cant_Max);
			compruebaCant(cant_Max);
		}
		i++;
	}
	return 0;
}