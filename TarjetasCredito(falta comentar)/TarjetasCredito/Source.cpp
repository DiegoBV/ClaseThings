/*
* bst.h
*
* Implementación del TAD arbol binario de búsqueda sin repeticiones con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Informática
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Martín Martín. All rights reserved.
*/

#ifndef BST_EDA_H_
#define BST_EDA_H_

#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw en graphAux
#include <iostream>
using namespace std;

/*
T: tipo de los elementos almacenados en el bst
Compare: clase que implementa operator() aceptando 2 referencias constantes a valores de tipo T, y devuelve
si el primer valor es "menor" que el segundo. Debe ser un 'strict weak ordering':
(1) irreflexivo, (2) asimétrico, (3) transitivo y con (4) transitividad de la incomparabilidad.
(Ver más detalles en https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings)
*/
template <typename T, typename Compare = less<T>>
class bst {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros unicos', uno al hijo izquierdo y al hijo derecho.
	*/
	class Nodo; // Declaración adelantada para poder definir Link
	using Link = shared_ptr<Nodo>; // Alias de tipo

	class Nodo {
	public:
		Link izq;
		T elem;
		Link der;

		Nodo(const T& elem) : izq(nullptr), elem(elem), der(nullptr) {}
		Nodo(Link izq, const T& elem, Link der) : izq(izq), elem(elem), der(der) {}
	};

	// puntero a la raíz
	Link raiz;

	// objeto comparador
	Compare cmp;


	// busqueda de nodo
	pair<bool, T> search_rec(const T& e, const Link& raiz) const {
		if (raiz == nullptr) {
			return pair<bool, T>(false, e);
		}
		else if (cmp(e, raiz->elem)) {
			return search_rec(e, raiz->izq);
		}
		else if (cmp(raiz->elem, e)) {
			return search_rec(e, raiz->der);
		}
		else { // e == nodo->elem
			return pair<bool, T>(true, raiz->elem);
		}
	}


	// cálculo recursivo del tamaño
	size_t size_rec(const Link& nodo) const {
		if (nodo == nullptr) {
			return 0;
		}
		else {
			return size_rec(nodo->izq) + size_rec(nodo->der) + 1;
		}
	}


	// inserción recursiva de elemento 
	void insert_rec(Link& raiz, const T& e) {
		if (raiz == nullptr) {
			raiz = make_shared<Nodo>(e);
		}
		else if (cmp(e, raiz->elem)) {
			insert_rec(raiz->izq, e);
		}
		else if (cmp(raiz->elem, e)) {
			insert_rec(raiz->der, e);
		}
		else {
			// Si e == raiz-elem el elemento ya esta, puedo lanzar una excepcion 
			// o no hacer nada
		}
	}


	// Dada la raiz de un árbol NO VACIO (es decir, raiz != nullptr), borra el nodo mínimo y 
	// devuelve el elemento que había ahí
	void remove_min(Link& raiz, T& min) {
		if (raiz->izq == nullptr) { // El nodo raiz contiene el mínimo
			min = raiz->elem;
			raiz = raiz->der; // El anterior nodo al que apuntaba raiz ya no tiene dueño, se libera la memoria
		}
		else {
			remove_min(raiz->izq, min);
		}
	}


	void remove_rec(Link& raiz, const T& e) {
		if (raiz == nullptr) // Imposible eliminar en árbol vacío
			return;

		if (cmp(e, raiz->elem)) {
			remove_rec(raiz->izq, e);
		}
		else if (cmp(raiz->elem, e)) {
			remove_rec(raiz->der, e);
		}
		else if (raiz->der == nullptr) { // e == raiz->elem
			raiz = raiz->izq;
		}
		else { // e == raiz->elem && raiz->der != nullptr
			T min;
			remove_min(raiz->der, min);
			raiz->elem = min;
		}
	}


	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph_rec(ostream & out, int indent, Link raiz) const {
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}


	// Realiza una copia de todos los nodos que cuelgan de 'raiz'
	Link copia(Link raiz) {
		if (raiz == nullptr) {
			return nullptr;
		}
		else {
			Link ni = copia(raiz->izq);
			Link nd = copia(raiz->der);
			return make_shared<Nodo>(ni, raiz->elem, nd);
		}
	}


public:
	// constructor de bst vacío
	bst() : raiz(nullptr) {}


	// constructor por copia
	bst(const bst<T, Compare>& other) {
		raiz = copia(other.raiz);
	}

	// Asignacion
	bst<T, Compare>& operator=(const bst<T, Compare>& other) {
		if (this != &other) {
			raiz.reset();
			raiz = copia(other.raiz);
		}
		return *this;
	}



	// saber si el bst es vacío 
	bool empty() const {
		return (raiz == nullptr);
	}


	// tamaño del bst
	size_t size() const {
		return size_rec(raiz);
	}

	// buscar un elemento
	pair<bool, T> search(const T& e) const {
		return search_rec(e, raiz);
	}


	// insertar un elemento
	void insert(const T& e) {
		insert_rec(raiz, e);
	}


	// borrar un elemento
	void remove(const T& e) {
		remove_rec(raiz, e);
	}


	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const {
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}
};

#endif /* BST_EDA_H_ */

#ifndef MAP_EDA_H_
#define MAP_EDA_H_
using namespace std;
template <typename Key, typename Value, typename Compare = less<Key>>
class map {
private:
	class FunctorPar {
	private:
		Compare cmp;
	public:
		bool operator() (const pair<Key, Value>& e1, const pair<Key, Value>& e2) const {
			return cmp(e1.first, e2.first);
		}
	};
	bst<pair<Key, Value>, FunctorPar> arbolBusqueda; //arbol de pares
	pair<Key, Value> parDefecto;
public: //HAY QUE INCLUIR EL COSTE DE TODOS LOS METODOOOOOS
	map() {}
	Value get(const Key& key) const {
		pair<bool, pair<Key, Value>> p = arbolBusqueda.search(pair<Key, Value>(key, parDefecto.second));
		if (p.first) {
			return p.second.second;
		}
		else {
			return 0; //si no está, devuelve 0
		}
	}

	bool contains(const Key& key) const {
		return arbolBusqueda.search(pair<Key, Value>(key, parDefecto.second)).first;
	}

	void insert(const Key& key, const Value& value) {
		/*if (!this->contains(key)) {
			arbolBusqueda.insert(pair<Key, Value>(key, value));
		}
		else {
			Value v = get(key);
			this->erase(key);
			arbolBusqueda.insert(pair<Key, Value>(key, v + value));
		}*/
		pair<bool, pair<Key, Value>> p = arbolBusqueda.search(pair<Key, Value>(key, parDefecto.second));
		if (!p.first) {
			arbolBusqueda.insert(pair<Key, Value>(key, value));
		}
		else {
			Value v = p.second.second;
			this->erase(key);
			arbolBusqueda.insert(pair<Key, Value>(key, v + value));
		}
	}


	void erase(const Key& key) {
		arbolBusqueda.remove(pair<Key, Value>(key, parDefecto.second));
	}
};
#endif /* MAP_EDA_H_ */

#include <vector>
#include <math.h>
void representa(vector <pair<int, float>>& aux) {
	for (size_t i = 0; i < aux.size(); i++) {
		cout << aux[i].first << " "  << fixed << setprecision(2) << aux[i].second << endl;
	}
	cout << endl;
}
int main() {
	int n;
	cin >> n;
	int i = 0;
	while (i < n) {
		map<int, float> dic;
		vector <pair<int, float>> aux;
		int m;
		cin >> m;
		int j = 0;
		while (j < m) {
			int TC;
			float money;
			cin >> TC >> money;		
			dic.insert(TC, money);
			j++;
		}

		int C;
		cin >> C;
		int k = 0;
		while (k < C) {
			int nC;
			cin >> nC;
			aux.push_back(pair<int, float>(nC, dic.get(nC)));
			k++;
		}
		representa(aux);
		i++;
	}
	system("pause");
	return 0;
}
















