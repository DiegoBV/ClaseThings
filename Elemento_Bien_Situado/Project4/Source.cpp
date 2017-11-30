//Grupo 22  Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción: 
/*
	Tras introducir el número de vectores que se quiere comprobar y el tamaño del vector, se invoca a la funcion elemento_BienSituado(...).
	En ella, se hace una primera comprobación. Si n (tamaño a comprobar) es menor que 2, se devuelve false si n = 0 (no ha encontrado un elemento bien situado),
	o true si ese elemento de encuentra en la posición correcta. Después hace la comprobación de si el elemento del medio esta bien situado y, si no, 
	se llama a la recursión. Se hace solo una llamada recursiva con n/2, lo que reduce el coste a O(Log(n)).
*/
#include <vector>
#include <iostream>
using namespace std;

//Funcion con coste O(Log(n)), donde n es fin - ini, es decir, el espacio recorrido en el vector
bool elemento_BienSituado(const vector < int >& v, int ini, int fin){
	//Atributes
	int med = (ini + fin)/ 2;
	int n = fin - ini;

	//Function
	if (n < 2){
		return (n == 0) ? false : (v[ini] == ini);
	}
	else if (v[med] == med) {
		return true;
	}
	else if (v[med] < med) {  //si v[med] < med, solo puede darse el caso de que se encuentre en la mitad desde med hasta fin, al ser un vector ordenado y sin repeticiones
		elemento_BienSituado(v, med, fin);
	}
	else if (v[med] > med) {  //si v[med] es > med, solo puede darse el caso de que se encuentre en la mitad desde ini hasta med
		elemento_BienSituado(v, ini, med);
	}
}

void rellenaVector(vector < int >& v) { //rellenar el vector con el input
	for (int i = 0; i < v.size(); i++) {
		cin >> v[i];
	}
}

void creaVector(vector < int >& v){
	//Atributes
	int tamanyo;

	//Function
	cin >> tamanyo;
	v.resize(tamanyo); //adapta el vector al tamaño que le indicamos
	rellenaVector(v);
}

int main(){
	//Atributes
	int n;
	int i = 0;
	vector <int> v;

	//Function
	cin >> n; //pide el numero de vectores que se quieres comprobar
	while (i < n) {
		creaVector(v);

		if (elemento_BienSituado(v, 0, v.size())) {  //si encuentra algun elemento bien situado --> "SI", si no --> "NO"
			cout << "SI" << endl;
		}
		else {
			cout << "NO" << endl;
		}
		i++;
	}
	return 0;
}