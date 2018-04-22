#pragma once
#include <vector>
using namespace std;
template <typename T>
class ManagerTemplate
{
protected:
	vector<T*> list;

public:

	ManagerTemplate(){

	}
	~ManagerTemplate(){
		for (T* it : list) {
			delete it;
		}
	}

	int size() { return list.size(); };

	T* getItem(int pos) { return list[pos]; }

	void pushSomething(T* newT) {
		list.push_back(newT);
	}
	
	T* addNewItem() { //hace un new T()
		T* nItem = new T();
		pushSomething(nItem);
		return nItem;
	}

	pair<bool, T*> getObjectPool() {
		int i = 0;
		bool found = false;
		T* aux = getItem(0);
		while (i < list.size() && !found) { //si encuentra el item inactivo, lo devuelve
			if (!getItem(i)->isActive()) {
				aux = getItem(i);
				found = true;
			}
			else 
				i++;
		}
		if (!found) { //si no lo ha encontrado, crea uno nuevo
			aux = addNewItem();
		}
		pair<bool, T*> par (found, aux);
		return par;
	}
	//vector<T> get() { return list; };
};

