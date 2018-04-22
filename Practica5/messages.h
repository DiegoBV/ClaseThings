#ifndef MESSAGES_H_
#define MESSAGES_H_
#include "GameObject.h"
#include "Asteroid.h"
#include "Bullets.h"

enum MessageId {
	BULLET_ASTROID_COLLISION,
	BULLET_FIGHTER_COLLISION,
	ASTROID_FIGHTER_COLLISION,
	FIGHTER_SHOOT,
	GAME_OVER,
	ROUND_START,
	ROUND_OVER,
	BULLET_CREATED,
	NO_MORE_ATROIDS,
	BADGE_ON,
	BADGE_OFF,
	SUPAH_ON,
	SUPAH_OFF,
	MULTI_ON,
	MULTI_OFF
};

struct Message {
	Message(MessageId id) :
		id_(id) {
	}
	MessageId id_;
};

struct BulletAstroidCollision : Message {
	BulletAstroidCollision(Bullets* bullet, Asteroid* astroid) :
		Message(BULLET_ASTROID_COLLISION), bullet_(bullet), astroid_(
			astroid) {
	}
	Bullets* bullet_;
	Asteroid* astroid_;
};

struct BulletFighterCollision : Message {
	BulletFighterCollision(GameObject* bullet, GameObject* fighter) :
		Message(BULLET_FIGHTER_COLLISION), bullet_(bullet), fighter_(
			fighter) {
	}
	GameObject* bullet_;
	GameObject* fighter_;
};

struct AstroidFighterCollision : Message {
	AstroidFighterCollision(GameObject* astroid, GameObject* fighter) :
		Message(ASTROID_FIGHTER_COLLISION), astroid_(astroid), fighter_(
			fighter) {
	}

	GameObject* astroid_;
	GameObject* fighter_;
};

struct FighterIsShooting : Message {
	FighterIsShooting(GameObject* fighter, vector<Vector2D>& bulletPosition,
		vector<Vector2D>& bulletVelocity) :
		Message(FIGHTER_SHOOT), fighter_(fighter), bulletPosition_(
			bulletPosition), bulletVelocity_(bulletVelocity) {
	}

	GameObject* fighter_;
	vector<Vector2D> bulletPosition_;
	vector<Vector2D> bulletVelocity_;
};
#endif /* MESSAGES_H_ */