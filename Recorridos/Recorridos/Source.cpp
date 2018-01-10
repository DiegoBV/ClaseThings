#include "bintree.h"
#include <vector>
#include <iostream>
using namespace std;

int main() {
	bintree<int> hji(2);
	bintree<int> hjd(0);
	bintree<int> hojaiz(hji, 10, hjd);
	bintree<int> hojader(50);
	bintree<int> arbol(hojaiz, 5, hojader);
	
	vector<int> v = arbol.preorder();
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	system("pause");
	//bintree* arbol = new bintree(nullptr, 5, nullptr);
	return 0;
}