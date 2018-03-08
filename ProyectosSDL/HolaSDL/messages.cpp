#include "messages.h"
#include "Fighter.h"


struct CollisionMessage : public Message {
	CollisionMessage(MessageId id, GameObject* o1, GameObject* o2) : Message(id), o1_(o1), o2_(o2) {}

	GameObject* o1_;
	GameObject* o2_;
};

struct AsteroidBulletCollisionMessage : public Message {
	AsteroidBulletCollisionMessage(MessageId id, Asteroid* o1, Bullets* o2) : Message(id), o1_(o1), o2_(o2) {}

	Asteroid* o1_;
	Bullets* o2_;
};

struct FighterBulletCollisionMessage : public Message {
	FighterBulletCollisionMessage(MessageId id, Fighter* o1, Bullets* o2) : Message(id), o1_(o1), o2_(o2) {}

	Fighter* o1_;
	Bullets* o2_;
};

struct FighterAsteroidCollisionMessage : public Message {
	FighterAsteroidCollisionMessage(MessageId id, Fighter* o1, Asteroid* o2) : Message(id), o1_(o1), o2_(o2) {}

	Fighter* o1_;
	Asteroid* o2_;
};


struct FighterShootMessage : public Message
{
	FighterShootMessage(Message id, GameObject* o) : Message(id), o_(static_cast<Fighter*>(o)) {}

	Fighter* o_;
};