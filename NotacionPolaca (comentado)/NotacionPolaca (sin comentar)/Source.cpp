//Grupo 22 Diego Baratto Valdivia / Alejandro Marín Pérez

//Descripción de la solución:
/*
Después de introducir el numero de casos de prueba que queremos considerar y la longitud de la cadena que vamos a introducir,
se invoca a la funcion calcula. En ella, recorre la cadena y almacena en la pila los numeros encontrados. Al encontrar un 
'+' o un '-', se llama a la funcion respectiva que hace el calculo (almacena en una variable el top de la pila, hace pop, almacena
en otra variable el top actual de la pila, vuelve a hacer pop, y hace push del resultado de la operacion de ambos operandos.
*/

#include <string>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int calcula(int L, string cadenaPolaca, stack<int>& pila);
void suma_Pila(stack<int>& pila);
void resta_Pila(stack<int>& pila);

//Funcion Main, donde se crea la pila y se recoge el número de casos de prueba que van a ser tratados. Además, guarda la longitud de la cadena a introducir y
// e invoca a la funcion calcula(...), la cual calcula la operacion en notación Polaca.
int main() {
	int op1, op2;
	stack<int> pila;
	int n;
	cin >> n;
	int i = 0;
	while (i < n) {
		int L;
		cin >> L;
		string cadena;
		cin >> cadena;
		cout << (calcula(L, cadena, pila)) << endl;
		i++;
	}
	system("pause");
	return 0;
}

//Funcion que calcula la operacion en notacion polaca. Su coste es O(L), siendo L la longitud de la cadena introducida, ya que tiene 
// que recorrerla entera para determinar el resultado de la operacion (los métodos de la pila son constantes).
int calcula(int L, string cadenaPolaca, stack<int>& pila) {
	for (int i = 0; i < L; i++) {
		if (cadenaPolaca[i] == '+') { //si es un más, invoca al metodo sumar
			suma_Pila(pila);
		}
		else if (cadenaPolaca[i] == '-') { //si es un menos, invoca al metodo restar
			resta_Pila(pila);
		}
		else {
			pila.push((int)cadenaPolaca[i] - 48); //si es un número, lo almacena en la pila (le resta 48 ya que 48 corresponde en hexadecimal con el caracter 0)
		}
	}
	return pila.top(); //return del ultimo elemento de la pila, el resultado final
}

//Funcion de suma, coste O(1)
void suma_Pila(stack<int>& pila) {
	int op1 = pila.top(); //almacena en una variable el top de la pila
	pila.pop(); //pop del mismo
	int op2 = pila.top(); 
	pila.pop();
	pila.push(op1 + op2); //push de los dos operandos sumados
}

//Funcion resta, coste 0(1)
void resta_Pila(stack<int>& pila) {
	int op1 = pila.top(); //almacena en una variable el top de la pila
	pila.pop(); //pop del mismo
	int op2 = pila.top();
	pila.pop();
	pila.push(op2 - op1); //push de los dos operandos restados
}