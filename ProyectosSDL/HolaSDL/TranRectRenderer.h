#ifndef TRANRECTRENDERER_H_
#define TRANRECTRENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class TranRectRenderer: public RenderComponent {
public:
	TranRectRenderer();
	virtual ~TranRectRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

#endif /* TRANRECTRENDERER_H_ */
