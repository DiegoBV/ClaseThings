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
	
	}
	int size() { return list.size(); };
	T getItem(int pos) { return *list[pos]; }
	void addItem(T newItem) {
		list.push_back(&(newItem));
	}

};

