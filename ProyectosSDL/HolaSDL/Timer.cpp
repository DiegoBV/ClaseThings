#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::update(GameObject * o, Uint32 time)
{
	if (on_ && timeOn_ + SECS < time) {  //si han pasado los 3 segundos, devuelvo true
		timeOn_ = time;
		//decirle a gameManager que han pasado los 10 segundos
		send(&Message(TIME_HAS_PASSED));
	}
}
