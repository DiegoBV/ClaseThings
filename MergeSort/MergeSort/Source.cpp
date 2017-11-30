#include <iostream>
#include <string>
#include <vector>
using namespace std;


void mergeSort(vector < int >& v, int ini, int fin);
void merge(vector < int >& v, int ini, int mid, int fin);
void rellenaVector(vector<int>& v);

int main() {
	//Atributes
	int n; //numero de vectores a rellenar
	int i = 0;
	vector <int> v;

	//Function
	cin >> n;
	while (i < n) {
		rellenaVector(v);
		mergeSort(v, 0, v.size());
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
		i++;
	}
	system("pause");
	return 0;
}

//Coste O(n*log(n)), donde n = fin - ini
void mergeSort(vector < int >& v, int ini, int fin) {
	//Atributes
	int n = fin - ini;
	int mid = (fin + ini) / 2;

	//Function
	if (n > 1) {
		mergeSort(v, ini, mid);
		mergeSort(v, mid, fin);
		merge(v, ini, mid, fin);
	}
}


void merge(vector < int >& v, int ini, int mid, int fin) {
	//Atributes
	int n1 = mid - ini;
	int n2 = fin - mid;
	vector <int> aux1;
	vector <int> aux2;
	aux1.resize(n1);
	aux2.resize(n2);

	//Function
	for (int q = ini, i = 0;  i < n1; q++, i++) {
		aux1[i] = v[q];
	}
	                                                      //copio los arrays desde ini hasta med y desde med hasta fin
	for (int q = mid, i = 0; i < n2; i++, q++) {
		aux2[i] = v[q];
	}

	
	int k = ini, i = 0, j = 0;
	while(i < n1 && j < n2) {
		
		if (aux1[i] <= aux2[j]) {
			v[k] = aux1[i];
			i++;
		}
		else if (aux1[i] > aux2[j]) {
			v[k] = aux2[j];
			j++;
		}
		k++;

	}

	//Copiar los elementos que sobren en esos arrays, quitando esto no funciona (?)
	while (i < n1) {
		v[k] = aux1[i];
		i++;
		k++;
	}

	while (j < n2) {
		v[k] = aux2[j];
		j++;
		k++;
	}



}

void rellenaVector(vector<int>& v) {
	//Atributes
	int tam;

	//Function
	cin >> tam;
	v.resize(tam);

	for (int i = 0; i < v.size(); i++) {
		cin >> v[i];
	}
}


