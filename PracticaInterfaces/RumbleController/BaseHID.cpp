#include "BaseHID.h"

void BaseHID::Actualiza()
{
	wLastButtons = wButtons;	//Store last state
	bConected = LeeMando();	//Read new state (virtual)

	if (bConected)
	{
		Mando2HID(); //get translated state

		//update buttons up/down
		wButtonsDown = (~wLastButtons) & (wButtons);
		wButtonsUp = (wLastButtons) & (~wButtons);

		//apply inercia
		if ((fThumbLX > 0.8) || (fThumbLX < -0.8)) velX = velX + 0.1*fThumbLX;
		else if ((fThumbLX > 0.01) || (fThumbLX < -0.01)) velX = (velX + fThumbLX) / 2;
		else velX = velX *(1 - 0.1);

		if ((fThumbLY > 0.8) || (fThumbLY < -0.8)) velX = velX + 0.1*fThumbLY;
		else if ((fThumbLY > 0.01) || (fThumbLY < -0.01)) velX = (velX + fThumbLY) / 2;
		else velX = velX *(1 - 0.1);

		//adjust inercia vel
		if (velX > 2.0) velX = 2.0;
		else if (velX < -2.0) velX = -2.0;
		if (velX > 2.0) velX = 2.0;
		else if (velX < -2.0) velX = -2.0;

		//update rotation states
		if ((fThumbLX > 0) && (fThumbLY > 0)) //restart
		{
			roState == pp; //positive-positive
			tRo = rotacionTime;
		}
		else if (tRo > 0)
		{
			tRo = tRo - T;
			if ((fThumbLX > 0) && (fThumbLY <= 0) && (roState == pp)) roState = pn;
			else if ((fThumbLX <= 0) && (fThumbLY < 0) && (roState == pn)) roState = nn;
			else if ((fThumbLX < 0) && (fThumbLY >= 0) && (roState == nn)) roState = np;
		}
		else roState = pp;

		if (tLR > 0) tLR -= T;
		else sLR(0.0, 0.0);
		if (tRR > 0) tRR -= T;
		else sRR(0.0, 0.0);

		EscribeMando();
	}
}
