#pragma once
template<class T>
class Destructor {
public:
	Destructor() :
		managedObj_(nullptr) {
	}
	Destructor(T* o) :
		managedObj_(o) {
	}
	virtual ~Destructor() {
		if (managedObj_ != nullptr)
			delete managedObj_;
	}
	void setObject(T* o) {
		managedObj_ = o;
	}
private:
	T * managedObj_;
};

