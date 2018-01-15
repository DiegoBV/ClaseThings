/*
* bst.h
*
* Implementaci�n del TAD arbol binario de b�squeda sin repeticiones con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Inform�tica
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Mart�n Mart�n. All rights reserved.
*/

#ifndef BST_EDA_H_
#define BST_EDA_H_

#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw en graphAux
using namespace std;

/*
T: tipo de los elementos almacenados en el bst
Compare: clase que implementa operator() aceptando 2 referencias constantes a valores de tipo T, y devuelve
si el primer valor es "menor" que el segundo. Debe ser un 'strict weak ordering':
(1) irreflexivo, (2) asim�trico, (3) transitivo y con (4) transitividad de la incomparabilidad.
(Ver m�s detalles en https://en.wikipedia.org/wiki/Weak_ordering#Strict_weak_orderings)
*/
template <typename T, typename Compare = less<T>>
class bst {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros unicos', uno al hijo izquierdo y al hijo derecho.
	*/
	class Nodo; // Declaraci�n adelantada para poder definir Link
	using Link = shared_ptr<Nodo>; // Alias de tipo

	class Nodo {
	public:
		Link izq;
		T elem;
		Link der;

		Nodo(const T& elem) : izq(nullptr), elem(elem), der(nullptr) {}
		Nodo(Link izq, const T& elem, Link der) : izq(izq), elem(elem), der(der) {}
	};

	// puntero a la ra�z
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
			return pair<bool, T>(true, e);
		}
	}


	// c�lculo recursivo del tama�o
	size_t size_rec(const Link& nodo) const {
		if (nodo == nullptr) {
			return 0;
		}
		else {
			return size_rec(nodo->izq) + size_rec(nodo->der) + 1;
		}
	}


	// inserci�n recursiva de elemento 
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


	// Dada la raiz de un �rbol NO VACIO (es decir, raiz != nullptr), borra el nodo m�nimo y 
	// devuelve el elemento que hab�a ah�
	void remove_min(Link& raiz, T& min) {
		if (raiz->izq == nullptr) { // El nodo raiz contiene el m�nimo
			min = raiz->elem;
			raiz = raiz->der; // El anterior nodo al que apuntaba raiz ya no tiene due�o, se libera la memoria
		}
		else {
			remove_min(raiz->izq, min);
		}
	}


	void remove_rec(Link& raiz, const T& e) {
		if (raiz == nullptr) // Imposible eliminar en �rbol vac�o
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


	// Muestra por 'out' una representaci�n del �rbol
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
	// constructor de bst vac�o
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



	// saber si el bst es vac�o 
	bool empty() const {
		return (raiz == nullptr);
	}


	// tama�o del bst
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


	// Muestra por 'out' una representaci�n del �rbol
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
	bst<pair<Key, Value>> arbolBusqueda; //arbol de pares
public:
	map() {}
	Value get(const Key& key) const {
		//pair<bool, Key> p = arbolBusqueda.search(key);
		//return p.second;
	}

	bool contains(const Key& key) const {
		return arbolBusqueda.search(key).first;
	}

	void insert(const Key& key, const Value& value) {
		arbolBusqueda.insert(pair<Key, Value>(key, value));
	}

	void erase(const Key& key) {
		arbolBusqueda.remove(key);
	}
};
#endif /* MAP_EDA_H_ */

#include <iostream>
int main() {
	map<int, char> dic;
	dic.insert(1, 'c');
	dic.insert(3, 'd');
	cout << dic.get((3));
	system("pause");
	return 0;
}


















