#ifndef SRC_SOUNDMANAGER_H_
#define SRC_SOUNDMANAGER_H_

#include "Observer.h"
#include "SDLGame.h"

/*
 *
 */
class SoundManager: public Observer {
public:
	SoundManager(SDLGame* game);
	virtual ~SoundManager();
	virtual void receive(Message msg);
private:
	SDLGame* game_;
};

#endif /* SRC_SOUNDMANAGER_H_ */
