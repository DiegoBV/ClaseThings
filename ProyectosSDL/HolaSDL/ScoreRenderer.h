#ifndef SCORERENDERER_H_
#define SCORERENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class ScoreRenderer: public RenderComponent {
public:
	ScoreRenderer();
	virtual ~ScoreRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

#endif /* SCORERENDERER_H_ */
