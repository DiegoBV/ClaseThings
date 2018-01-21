#include <vector>
#include <iostream>
#include <queue>
using namespace std;
//Grupo 22 Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción de la solución:
/*
Después de introducir el numero de casos de prueba que queremos considerar, se realizan los recorridos inorder, postorder, por niveles y preorder de los árboles que nos
introduzcan
*/


/*
* bintree_eda.h
*
* Implementación del TAD arbol binario con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Informática
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Martín Martín. All rights reserved.
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

/*
* bintree_eda.h
*
* Implementación del TAD arbol binario con nodos enlazados usando shared_ptr
*
*  Estructuras de Datos y Algoritmos
*  Facultad de Informática
*  Universidad Complutense de Madrid
*
*  Copyright (c) 2017 Enrique Martín Martín. All rights reserved.
*/
#ifndef BINTREE_EDA_H_
#define BINTREE_EDA_H_

#include <stdexcept> // domain_error
#include <algorithm> // max
#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw
#include <vector>
#include <queue>
using namespace std;


template <typename T>
class bintree {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros compartidos', uno al hijo izquierdo y al hijo derecho.
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

	// constructora privada a partir de un puntero a Nodo
	// Para construir los árboles generados por left() y right()
	bintree(Link r) : raiz(r) {} // O(1)

								 // Muestra por 'out' una representación del árbol
								 // Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015

	void graph_rec(ostream & out, int indent, Link raiz) const { // O(n), donde 'n' es el número de nodos alcanzables desde 'raiz'
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}

	void preorder_rec(vector<T>& v, Link n) const { //preorder recursivo, O(n), donde n es el número de nodos del árbol
		if (n->elem != 0 && n != nullptr) {
			v.push_back(n->elem); //push de la raiz del elemento de la raiz

			if (n->izq != nullptr)
				preorder_rec(v, n->izq); //si el hijo izquierdo no es nulo, recursion por la izquierda

			if (n->der != nullptr)
				preorder_rec(v, n->der); //si el hijo derecho no es nulo, recursion por la derecha
		}
	}

	void inorder_rec(vector<T>& v, Link n) const { //Inorder recursivo, O(n), donde n es el número de nodos del árbol
		if (n->elem != 0 && n != nullptr) {
			if (n->izq != nullptr) //primero se recorre por la izquierda
				inorder_rec(v, n->izq);

			v.push_back(n->elem); //se pushea el elemento

			if (n->der != nullptr) //se recorre por la derecha
				inorder_rec(v, n->der);
		}
	}

	void postorder_rec(vector<T>& v, Link n) const { //Postorder recursivo, O(n), donde n es el número de nodos del árbol
		if (n != nullptr && n->elem != 0) {
			if (n->izq != nullptr)
				postorder_rec(v, n->izq);

			if (n->der != nullptr)
				postorder_rec(v, n->der);

			v.push_back(n->elem);
		}
	}

	void levels_it(vector<T>& v, Link n) const { //recorrido por niveles, O(n), donde n es el numero de nodos del árbol
		if (n->elem != 0 && n != nullptr) {
			queue<Link> cola; //usamos una cola de ayuda
			cola.push(n); //push del nodo N
			while (!cola.empty()) { //meintras no este vacía
				Link aux = cola.front(); //cogemos el primer elemento que entró
				v.push_back(aux->elem); //guardamos
				cola.pop(); //popeamos
				if (aux->izq->elem != 0 && aux->izq != nullptr) { cola.push(aux->izq); } //si el izquierdo no es nulo, lo guardamos
				if (aux->der->elem != 0 && aux->der != nullptr) { cola.push(aux->der); } //si el derecho no es nulo, lo guardamos
			}
		}
	}

public:
	// constructor de árbol vacío
	bintree() : raiz(nullptr) {} // O(1)

								 // constructor de árbol hoja
	bintree(const T& elem) : raiz(make_shared<Nodo>(elem)) {} // O(1)

															  // constructor de árbol con 2 hijos
	bintree(const bintree<T>& izq, const T& elem, const bintree<T>& der) : // O(1)
		raiz(make_shared<Nodo>(izq.raiz, elem, der.raiz)) {}

	// valor en la raíz (si existe)
	const T& root() const { // O(1)
		if (empty()) {
			throw std::domain_error("No hay raiz en arbol vacio");
		}
		else {
			return raiz->elem;
		}
	}

	// hijo izquierdo (si existe)
	bintree<T> left() const { // O(1)
		return bintree(raiz->izq);
	}

	// hijo derecho (si existe)
	bintree<T> right() const { // O(1)
		return bintree(raiz->der);
	}

	// saber si el árbol es vacío 
	bool empty() const { // O(1)
		return (raiz == nullptr);
	}

	// altura del árbol
	size_t height() const { // O(n), donde 'n' es el número de nodos en el árbol
		if (empty()) {
			return 0;
		}
		else {
			size_t hl = left().height();
			size_t hr = right().height();
			return max<size_t>(hl, hr) + 1;
		}
	}

	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el número de nodos en el árbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}

	vector<T> preorder() const {
		vector<T> v;
		preorder_rec(v, raiz); //O(n)
		return v;
	}

	vector<T> inorder() const {
		vector<T> v;
		inorder_rec(v, raiz); //O(n)
		return v;
	}

	vector<T> postorder() const {
		vector<T> v;
		postorder_rec(v, raiz); //O(n)
		return v;
	}

	vector<T> levels() const {
		vector<T> v;
		levels_it(v, raiz); //O(n)
		return v;
	}
};

#endif /* BINTREE_EDA_H_ */


bintree<int> entrada() { //construccion del arbol de forma recursiva
	int elemRaiz;
	cin >> elemRaiz;
	if (elemRaiz != 0) {
		bintree<int> hojaIzq = entrada();
		bintree<int> hojaDer = entrada();
		bintree<int> arbol(hojaIzq, elemRaiz, hojaDer);
		return arbol;
	}
	else {
		bintree<int> arbol(elemRaiz);
		return arbol;
	}

}

void representa_Vector(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		if (i == v.size() - 1) {
			cout << v[i];
		}
		else {
			cout << v[i] << " ";
		}
	}
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	int i = 0;
	while (i < n) {
		bintree<int> arbol = entrada();
		vector<int> v = arbol.preorder();
		representa_Vector(v);
		v = arbol.inorder();
		representa_Vector(v);
		v = arbol.postorder();
		representa_Vector(v);
		v = arbol.levels();
		representa_Vector(v);
		cout << "==" << endl;
		i++;
	}
	system("pause");
	return 0;
}