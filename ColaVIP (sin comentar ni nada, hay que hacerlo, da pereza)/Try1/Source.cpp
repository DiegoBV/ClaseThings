#include <iostream>
using namespace std;
#ifndef ColaVIP_H_
#define ColaVIP_H_
template <typename T>
class ColaVIP
{
private:
	class Nodo {
		public:
		T elemento;
		int prioridad;
		Nodo* sig;
		Nodo(const T& e, const int& p, Nodo* nod) : elemento(e), prioridad(p), sig(nod) {}
		Nodo() : sig(nullptr) {}
	};

	size_t numElementos;
	int prioridadMax;
	Nodo* ghost;
	Nodo* ultimo;
	Nodo* recorre_Cola(int p);
	void libera();

public:
	ColaVIP() {};
	~ColaVIP() { libera(); };
	ColaVIP(int p);
	void push(int p, const T& elem); //clave
	void pop();
	bool empty() const;
	size_t size() const;
	void draw();
};

template <typename T>
ColaVIP<T>::ColaVIP(int p) {
	prioridadMax = p;
	ultimo = nullptr;
	ghost = new Nodo();
	numElementos = 0;
}

template <typename T>
typename ColaVIP<T>::Nodo* ColaVIP<T>::recorre_Cola(int p) {
	Nodo* aux = ghost;
	while (aux->sig != nullptr && p >= aux->sig->prioridad) {
		aux = aux->sig;
	}
	return aux;
}

template <typename T>
void ColaVIP<T>::push(int p, const T& elem) {
	if (empty()) {
		Nodo* newNodo = new Nodo(elem, p , nullptr);
		ghost->sig = newNodo;
	}
	else {
		Nodo* anterior = recorre_Cola(p);
		Nodo* newNodo = new Nodo(elem, p , anterior->sig);
		anterior->sig = newNodo;
	}
	numElementos++;
}

template <typename T>
void ColaVIP<T>::pop() {
	numElementos--;
	Nodo* aux = ghost->sig;
	ghost->sig = aux->sig;
	delete aux;
}

template <typename T>
bool ColaVIP<T>::empty() const {
	return numElementos == 0;
}

template <typename T>
size_t ColaVIP<T>::size() const {
	return numElementos;
}
template <typename T>
void ColaVIP<T>::libera() {
	Nodo* aux = ghost->sig;
	while (aux != nullptr) {
		Nodo* deleteable = aux;
		aux = aux->sig;
		delete deleteable;
	}
	delete ghost;
}

template <typename T>
void ColaVIP<T>::draw() {
	Nodo* n = ghost;
	if (this->empty()) {
		cout << "NADIE";
	}
	else {
		while (!(n->sig == nullptr)) {
			cout << n->sig->elemento << " ";
			n = n->sig;
		}
	}
}
#endif /* ColaVIP_H_ */

int main() {
	int n = 0;
	cin >> n;
	int i = 0;
	while (i < n) {
		int p;
		cin >> p;
		ColaVIP<int>* cola = new ColaVIP<int>(p);
		int lleSal;
		cin >> lleSal;
		int aforoMax;
		cin >> aforoMax;
		int j = 0;
		int aforoActual = 0;
		while (j < lleSal) {
			char c;
			cin >> c;
			if (c == '+') {
				int prioridad, identificador;
				cin >> prioridad >> identificador;
				if (aforoActual < aforoMax) {
					aforoActual++;
				}
				else {
					cola->push(prioridad, identificador);
				}
			}
			else {
				aforoActual--;
				if (aforoActual == aforoMax - 1 && !cola->empty()) {
					cola->pop(); //entra el primero por prioridad
					aforoActual++;
				}
			}
			j++;
		}
		cola->draw();
		cout << endl;
		i++;
	}
	system("pause");
	return 0;
}