#ifndef SRC_MESSAGES_H_
#define SRC_MESSAGES_H_
#include "GameObject.h"
enum MessageId { BALL_TOUCHES_WALL, BALL_TOUCHES_PADDLE, ROUND_START, ROUND_END, BALL_LEAVES_RIGHT, BALL_LEAVES_LEFT, HIT, 
	BULLET_ASTEROID_COLISION, BULLET_FIGHTER_COLLISION, FIGHTER_SHOOT};

struct Message {
	Message(MessageId id) : id_(id) {
	}
	MessageId id_;
};

struct CollisionMessage: public Message {
	CollisionMessage(MessageId id, GameObject* o1, GameObject* o2) : Message(id), o1_(o1), o2_(o2) {
	}
	MessageId id_;
	GameObject* o1_;
	GameObject* o2_;
};


#endif /* SRC_MESSAGES_H_ */
