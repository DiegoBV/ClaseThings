#include <string>
#include <stack>
#include <string>
#include <iostream>

using namespace std;

int calcula(int L, string cadenaPolaca, stack<int>& pila);
void suma_Pila(stack<int>& pila);
void resta_Pila(stack<int>& pila);

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

int calcula(int L, string cadenaPolaca, stack<int>& pila) {
	for (int i = 0; i < L; i++) {
		if (cadenaPolaca[i] == '+') {
			suma_Pila(pila);
		}
		else if (cadenaPolaca[i] == '-') {
			resta_Pila(pila);
		}
		else {
			pila.push((int)cadenaPolaca[i] - 48);
		}
	}
	return pila.top();
}

void suma_Pila(stack<int>& pila) {
	int op1 = pila.top();
	pila.pop();
	int op2 = pila.top();
	pila.pop();
	pila.push(op1 + op2);
}

void resta_Pila(stack<int>& pila) {
	int op1 = pila.top();
	pila.pop();
	int op2 = pila.top();
	pila.pop();
	pila.push(op2 - op1);
}