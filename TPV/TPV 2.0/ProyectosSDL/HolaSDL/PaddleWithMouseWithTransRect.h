#ifndef PADDLEWITHMOUSEWITHTRANSRECT_H_
#define PADDLEWITHMOUSEWITHTRANSRECT_H_

#include "PaddleWithMouse.h"

/*
 *
 */
class PaddleWithMouseWithTransRect: public PaddleWithMouse {
public:
	PaddleWithMouseWithTransRect(SDLGame* game);
	virtual ~PaddleWithMouseWithTransRect();
	virtual void render(Uint32 time);

};

#endif /* PADDLEWITHMOUSEWITHTRANSRECT_H_ */
