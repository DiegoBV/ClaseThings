#include "bintree.h"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int main() {
	bintree<int> hji(2);
	bintree<int> hjd(3);
	bintree<int> hojaiz(hji, 10, hjd);
	bintree<int> hj2(100);
	bintree<int> hj3(200);
	bintree<int> hojader(hj2, 50, hj3);
	bintree<int> arbol(hojaiz, 5, hojader);
	
	vector<int> v = arbol.levels();
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	system("pause");
	//bintree* arbol = new bintree(nullptr, 5, nullptr);
	return 0;
}