//Grupo 22 Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción de la solución:
/*
Para calcular el numero maximo de personas en un momento y que el caso proporcionado por el enunciado sea consistente, se hace uso de un diccionario que almacena
las personas por su Nombre y un vector que ordena dichas entradas y salidas por tiempo (útil para saber si una persona que sale estaba realmente o una persona que entra
realmente no estaba).
*/

#include <iostream>
#include <map>
#include <string>
using namespace std;

void swap_Max(int& newNum, int& maxNum) { //comprueba si el numero actual de personas es mayor, si lo es lo sustituye O(1)
	if (newNum > maxNum) {
		maxNum = newNum;
	}
}
//O(n), siendo n la altura del árbol
void entradaCocina(map<string, int>& dic, bool& consistente, const string& newKey, const int& newTime, int& numPersonas, int& numMax) {
	size_t size = dic.size(); //O(1)
	dic.insert(pair<string, int>(newKey, newTime)); //O(n), siendo n la altura del árbol, ya que típicamente se representan con árboles binarios de búsqueda
	size_t sizeAux = dic.size(); //O(1)
	if (size == sizeAux) { //si son iguales, quiere decir que no ha insertado nada porque ya estaba --> consistente = false
		consistente = false;
	}
	else {
		numPersonas++; //entra y aumenta el numero de personas
		swap_Max(numPersonas, numMax); //comprobamos si el numero de personas actual es mayor que el maximo hasta ahora
	}
}

//O(n), siendo n la altura del árbol
void salidaCocina(map<string, int>& dic, bool& consistente, const string& oldKey, int& numPersonas) {
	size_t size = dic.size();
	dic.erase(oldKey); //borramos, coste O(n), siendo n la altura del árbol
	size_t sizeAux = dic.size();
	if (size == sizeAux) { //si son iguales, quiere decir que no ha borrado nada porque no estaba ---> consistente = false
		consistente = false;
	}
	else {
		numPersonas--; //decrementamos numero de personas si realmente se encontraba allí
	}	
}

void representa(bool& consistente, int& numMax) {
	if (consistente) { //si la lista es consistente, imprime por pantalla el numero maximo de personas
		cout << numMax << endl;
	}
	else {
		cout << "ERROR" << endl; //si no, imprime "ERROR"
	}
}
#include <vector>
#include <algorithm>

//Coste O(n), donde n es el numero de elementos del vector
void resuelve(vector <pair<pair<int, string>, int>>& v, map<string, int>& dic, bool& consistente, int& numPersonas, int& numMax) {
	for (size_t i = 0; i < v.size() && consistente; i++) { // mientras no llegue al final o sea consistente (para ahorrar tiempo vaya)
		if (v[i].second == 0) { //si es 0, significa que hay una salida
			salidaCocina(dic, consistente, v[i].first.second, numPersonas); //lo saca si puede, si no, consistente = false
		}
		else if(v[i].second == 1){ //si es un 1, significa que hay una entrada
			entradaCocina(dic, consistente, v[i].first.second, v[i].first.first, numPersonas, numMax); //lo inserta si puede, si no, consistente = false
		}
	}
	representa(consistente, numMax); //tras acabar el recorrido, resuelve
}

struct op{ //operador comparador, nos sirve para ordenar el vector solo por tiempo
	bool operator() (pair<pair<int, string>, int> p1, pair<pair<int, string>, int> p2) { return (p1.first.first < p2.first.first); }
} comparador;


int main() {
	int E; //ENTRADAS
	int S; //SALIDA
	cin >> E >> S;
	while (E != -1 && S != -1) { //caso especial que para el bucle
		map<string, int> dic;
		vector <pair<pair<int, string>, int>> v;
		bool consistente = true;
		int numPersonasCocina = 0;
		int numMax = 0;
		int i = 0;
		while (i < E) {
			int time;
			string name;
			cin >> time >> name; //recoge el nombre y el tiempo y las inserta
			pair<int, string> p(time, name);
			pair<pair<int, string>, int > p2(p, 1); //lo mete en el vector con el segundo elemento "1" que indica que es una entrada
			v.push_back(p2);
			i++;
		}

		int j = 0;

		while (j < S) {
			int time;
			string name;
			cin >> time >> name;
			pair<int, string> p(time, name);
			pair<pair<int, string>, int > p2(p, 0); //lo mete en el vector con el segundo elemento "0" que indica que es una salida
			v.push_back(p2);
			j++;
		}
		sort(v.begin(), v.end(), comparador); //ordena el vector por tiempos de entrada/salida
		resuelve(v, dic, consistente, numPersonasCocina, numMax); //resuelve y representa la solución
		cin >> E >> S;
	}
	return 0;
}

