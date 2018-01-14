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
#include <queue>
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


	bool contNodos_rec(const T& e, const Link& raiz, int& numNodos, queue<T>& colaAux) const {
		if (raiz == nullptr) {
			return false;
		}
		else if (cmp(e, raiz->elem)) {
			if (colaAux.empty() && raiz->izq != nullptr) { //si la cola esta vacia, pusheamos el izquiero y sumamos 1
				numNodos++;
				colaAux.push(raiz->izq->elem);
				return contNodos_rec(e, raiz->izq, numNodos, colaAux);
			}
			else if (raiz->izq != nullptr) { //si no esta vacia, comprobamos que no sea la primera de la cola (ya hemos pasado por él)
				if (colaAux.front() != raiz->izq->elem) {
					numNodos++;
					colaAux.push(raiz->izq->elem);
				}
				else {
					numNodos--;
					colaAux.pop();
				}
				return contNodos_rec(e, raiz->izq, numNodos, colaAux);
			}
		}
		else if (cmp(raiz->elem, e)) {
			if (colaAux.empty() && raiz->der != nullptr) {
				numNodos++;
				colaAux.push(raiz->der->elem);
				return contNodos_rec(e, raiz->der, numNodos, colaAux);
			}
			else if (raiz->der != nullptr ) {
				if (colaAux.front() != raiz->der->elem) {
					numNodos++;
					colaAux.push(raiz->der->elem);
				}
				else {
					numNodos--;
					colaAux.pop();
				}
				return contNodos_rec(e, raiz->der, numNodos, colaAux);
			}		
		}
		else {
			return true;
		}
	}

	// busqueda de nodo
	bool search_rec(const T& e, const Link& raiz) const {
		if (raiz == nullptr) {
			return false;
		}
		else if (cmp(e, raiz->elem)) {
			return search_rec(e, raiz->izq);
		}
		else if (cmp(raiz->elem, e)) {
			return search_rec(e, raiz->der);
		}
		else { // e == nodo->elem
			return true;
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

	// cálculo recursivo de la altura 
	size_t height(const Link& nodo) const {
		if (nodo == nullptr) {
			return 0;
		}
		else {
			return max(height(nodo->izq), height(nodo->der)) + 1;
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

	int diametro_rec(Link n) const {
		if (n != nullptr) {
			int leftHeight = height(n->izq); //calculamos la altura del hijo izquierdo
			int rightHeight = height(n->der); //calculamos la altura del hijo derecho
			int leftDiametro = diametro_rec(n->izq); //calculamos el diametro del hijo izquierdo (puede darse el caso de que el diam max no se encuentre pasando la raiz...)
			int rightDiametro = diametro_rec(n->der); //same para el derecho
			int diam = max(leftHeight + rightHeight + 1, max(leftDiametro, rightDiametro));
			//calculamos el maximo entre las dos alturas + 1 (la raiz) y el maximo entre los diametros de los hijos (esto es to dificil de explicar con palabras)
			return diam;
		}
		else {
			return 0; //caso de que sea nullptr
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
	bool search(const T& e) const {
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

	int distancia(const T& a, const T& b){
		int numNodos = 0;
		int numNodosA = 0;
		int numNodosB = 0;
		Link root = raiz;
		queue<T> colaAux;
		contNodos_rec(a, root, numNodosA, colaAux);
		contNodos_rec(b, root, numNodosB, colaAux);
		numNodos = numNodosA + numNodosB;
		return numNodos;
	}
	
	int diametro() const {
		return diametro_rec(raiz) - 1;
	}
};

#endif /* BST_EDA_H_ */

#include <fstream>
#include <iostream>

void calcula(queue<int>& c, bst<int>& arbol) {
	if (arbol.empty()) {
		cout << endl;
	}
	else {
		cout << arbol.diametro() << endl;
		while (c.size() != 0) {
			int A = c.front();
			c.pop();
			int B = c.front();
			c.pop();
			cout << arbol.distancia(A, B) << endl;
		}
	}
}
int main() {
	int n;
	cin >> n; //casos de prueba
	int i = 0;
	while (i < n) {
		bst<int> arbol;
		queue<int> distancias;
		int m;
		cin >> m; //elementos en el arbol
		int j = 0;
		while (j < m) {
			int numAIntroducir;
			cin >> numAIntroducir;
			arbol.insert(numAIntroducir);
			j++;
		}
		int d;
		cin >> d; //distancias a introducir
		int k = 0;
		while (k < d) {
			int A, B;
			cin >> A >> B;
			distancias.push(A);
			distancias.push(B);
			k++;
		}
		/*std::filebuf fb;
		fb.open("test.txt", std::ios::out);
		std::ostream os(&fb);
		arbol.graph(os);*/ 

		calcula(distancias, arbol);
		i++;
	}
	system("pause");
	return 0;
}