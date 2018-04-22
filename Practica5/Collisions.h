#ifndef SRC_SIMPLEENGINE_BASE_COLLISIONS_H_
#define SRC_SIMPLEENGINE_BASE_COLLISIONS_H_

#include "Vector2D.h"
#include "GameObject.h"

/*
 *
 */
class Collisions {
public:
	Collisions();
	virtual ~Collisions();

	static bool collides(GameObject* o1, GameObject* o2);
	static bool collidesWithRotation(GameObject* o1, GameObject* o2);
	static bool PointInTriangle(Vector2D A, Vector2D B, Vector2D C, Vector2D P);
	static bool PointInRectangle(Vector2D X, Vector2D Y, Vector2D Z, Vector2D W, Vector2D P);

};

#endif /* SRC_SIMPLEENGINE_BASE_COLLISIONS_H_ */
