#ifndef SRC_SOUNDMANAGER_H_
#define SRC_SOUNDMANAGER_H_

#include "Observer.h"
#include "ManagerTemplate.h"

/*
 *
 */
class SoundManager: public Observer {
public:
	SoundManager() {}
	SoundManager(SDLGame* game);
	virtual ~SoundManager();
	virtual void receive(Message* msg);
private:
	SDLGame* game_;
};

#endif /* SRC_SOUNDMANAGER_H_ */
