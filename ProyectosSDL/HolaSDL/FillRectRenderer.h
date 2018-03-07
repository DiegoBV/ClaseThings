#ifndef FILLRECTRENDERER_H_
#define FILLRECTRENDERER_H_

#include "RenderComponent.h"

/*
 *
 */
class FillRectRenderer : public RenderComponent {
public:
	FillRectRenderer();
	virtual ~FillRectRenderer();
	virtual void render(GameObject* o, Uint32 time);
};

#endif /* FILLRECTRENDERER_H_ */
