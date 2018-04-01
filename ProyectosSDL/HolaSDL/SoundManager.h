#ifndef SRC_SOUNDMANAGER_H_
#define SRC_SOUNDMANAGER_H_

#include "Observer.h"
#include "ManagerTemplate.h"
#include <queue>

/*
 *
 */
class SoundManager: public Observer, public Container {
public:
	SoundManager() {}
	SoundManager(SDLGame* game);
	virtual ~SoundManager();
	virtual void receive(Message* msg);
	virtual void update(Uint32 time);
private:
	struct PlayMessage {
		PlayMessage(Resources::SoundEffectId id, int num) : id_(id), num_(num) {};
		Resources::SoundEffectId id_; //id del sonido a reproducir
		int num_;
	};
	queue<PlayMessage> eventQueue;
};

#endif /* SRC_SOUNDMANAGER_H_ */
