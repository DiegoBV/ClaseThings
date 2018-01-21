//Grupo 22 Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción de la solución:
/*
Después de introducir el numero de casos de prueba que queremos considerar y la prioridad maxima, comienza a pedirle al usuario
que introduzca el numero de entradas, salidas y dichos casos. Para manegar la cola VIP, al hacer push de una persona con 
su prioridad asociada, en dicho metodo se le coloca en el lugar que le corresponde. Los demás métodos solo extraen el primer elemento 
de la cola para poder manejarla con facilidad.
*/

#include <iostream>
using namespace std;
//Template Cola VIP
#ifndef ColaVIP_H_
#define ColaVIP_H_
template <typename T>
class ColaVIP
{
private:
	//Definicion de la clase Nodo, tiene un elemento, una prioridad asociada y un puntero a su nodo siguiente
	class Nodo {
		public:
		T elemento;
		int prioridad;
		Nodo* sig;
		Nodo(const T& e, const int& p, Nodo* nod) : elemento(e), prioridad(p), sig(nod) {}
		Nodo() : sig(nullptr) {}
	};

	size_t numElementos; //numero de elementos totales
	int prioridadMax; //p max
	Nodo* ghost; //nodo fantasma auxiliar
	Nodo* recorre_Cola(int p); //recorre la cola hasta llegar al lugar especificado
	void libera(); //libera memoria

public:
	ColaVIP() {}; //constructor por defecto
	~ColaVIP() { libera(); }; //destructor
	ColaVIP(int p); //construcor de la cola
	void push(int p, const T& elem); //clave
	void pop();
	T const& front() const;
	bool empty() const;
	size_t size() const;
	void draw();
};

template <typename T>
ColaVIP<T>::ColaVIP(int p) {
	prioridadMax = p;
	ghost = new Nodo(); //nodo vacío
	numElementos = 0;
}

//Método de coste O(p), donde p es la prioridad a buscar (p <= prioridadMax). En el caso peor recorre la cola entera
template <typename T>
typename ColaVIP<T>::Nodo* ColaVIP<T>::recorre_Cola(int p) {
	Nodo* aux = ghost; //nodo auxiliar
	while (aux->sig != nullptr && p >= aux->sig->prioridad) { //mientras el siguiente del nodo auxiliar no sea null y p >= priorirdad del siguiente, aún no la ha encontrado
		aux = aux->sig;
	}
	return aux; //return de dicho nodo
}

//Inserta un elemento + prioridad en la cola VIP en su posición correspondiente. Coste O(p), donde p es la prioridad de dicho elemento (recorre_Cola tiene coste lineal, por
//ello este método tiene dicho coste, los demás son constantes)
template <typename T>
void ColaVIP<T>::push(int p, const T& elem) {
	if (empty()) { //si la cola es vacia, crea un nuevo nodo y hace que ghost->sig le apunte
		Nodo* newNodo = new Nodo(elem, p , nullptr);
		ghost->sig = newNodo;
	}
	else { //si no. recorre la cola para saber en que posicion colocarle y enlaza punteros
		Nodo* anterior = recorre_Cola(p);
		Nodo* newNodo = new Nodo(elem, p , anterior->sig);
		anterior->sig = newNodo;
	}
	numElementos++; //aumenta numero de elementos
}

//Coste O(1), elimina el primer elemento de la cola
template <typename T>
void ColaVIP<T>::pop() {
	numElementos--; //reduce num de elementos
	Nodo* aux = ghost->sig; //aux que apunta al primer nodo
	ghost->sig = aux->sig; //el primerpo ahora es el siguiente del primero
	delete aux; //delete
}

//Coste O(1), devuelve el primer elemento de la cola
template <typename T>
T const& ColaVIP<T>::front() const {
	return ghost->sig->elemento;
}

//Coste O(1), comprueba si numElementos es 0 (vacía) o no
template <typename T>
bool ColaVIP<T>::empty() const {
	return numElementos == 0;
}

//Coste O(1), devuelve numElementos
template <typename T>
size_t ColaVIP<T>::size() const {
	return numElementos;
}

//Coste O(n), donde, n = numElementos totales de la cola, la recorre eliminando dichos nodos
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

//Coste O(n), donde n = numElementos. Recorre la cola mostrando por consola los elementos ordenados
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

//Funcion main
int main() {
	int n = 0;
	cin >> n;
	int i = 0;
	while (i < n) { //casos de prueba
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
			if (c == '+') { //si el char introducido es un '+', se comprueba que no se haya superado el aforoMax
				int prioridad, identificador;
				cin >> prioridad >> identificador;
				if (aforoActual < aforoMax) { //si no se ha superado, se aumenta el aforoActual
					aforoActual++;
				}
				else { //si se superó, se añade un nuevo elemento a la cola
					cola->push(prioridad, identificador);
				}
			}
			else { //si es un menos, disminuye el aforoActual
				aforoActual--;
				if (aforoActual == aforoMax - 1 && !cola->empty()) { //si aforoActual era igual que AforoMax y la cola no está vacia, se hace un pop de la cola y se aumenta el aforoActual
					cola->pop(); //entra el primero por prioridad
					aforoActual++;
				}
			}
			j++;
		}
		cola->draw(); //se muestra la cola por pantalla
		cout << endl;
		i++;
	}
	system("pause");
	return 0;
}