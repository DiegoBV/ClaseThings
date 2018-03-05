#pragma once
#include <vector>
using namespace std;
template <typename T>
class ManagerTemplate
{
protected:
	vector<T> list;

public:

	ManagerTemplate(){

	}
	~ManagerTemplate(){
	
	}

	int size() { return list.size(); };

	T* getItem(int pos) { return &list[pos]; }

	void addNewItem(T newItem) {
		list.push_back(newItem);
	}

	pair<bool, T*> getObjectPool() {
		int i = 0;
		bool found = false;
		T* aux = getItem(0);
		while (i < list.size() && !found) { //si encuentra el item inactivo, lo devuelve
			if (!(*getItem(i))->isActive()) {
				aux = getItem(i);
				(*aux)->setActive(true);
				found = true;
			}
			else 
				i++;
		}
		if (!found) { //si no lo ha encontrado, crea uno nuevo
			aux = new T(*aux); //no funciona, modifica todo el rato el mismo T_T hace un new Asteroid*() y no se hacer new Asteroid() desde aqui-->preguntar al profe
			addNewItem(*aux);
		}
		pair<bool, T*> par (found, aux);
		return par;
	}
	//vector<T> get() { return list; };
};

