#pragma once
#include "Observable.h"
class CollisionManager: public Observable //a�adiria a su lista de observers manager de ast y balas y el fighter para mandarles el mensaje de que han chocado
{
public:
	CollisionManager();
	~CollisionManager();
};

