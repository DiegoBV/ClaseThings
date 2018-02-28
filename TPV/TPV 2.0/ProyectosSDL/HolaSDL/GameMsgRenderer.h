#ifndef GAMEMSGRENDERER_H_
#define GAMEMSGRENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class GameMsgRenderer: public RenderComponent {
public:
	GameMsgRenderer();
	virtual ~GameMsgRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

#endif /* GAMEMSGRENDERER_H_ */
