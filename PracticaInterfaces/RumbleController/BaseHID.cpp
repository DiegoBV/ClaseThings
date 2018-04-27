#include "BaseHID.h"

void BaseHID::Actualiza()
{
	wLastButtons = wButtons; //Copia estado de botones
	bConected = LeeMando(); //Leo Mando
	if (bConected == true)
	{
		Mando2HID(); //Vuelco de Mando a HID normalizando
					 //Actualizo Gestos de entrada genéricos (entradas)
					 //Genero Gesto de feedback (salida)

		wButtonsDown = (-wLastButtons) & (wButtons);
		wButtonsUp = (wLastButtons) & (-wButtons);

		fThumbLXf = (1 - a) + fThumbLXf + a*fThumbLX;
		fThumbLYf = (1 - a) + fThumbLYf + a*fThumbLY;

		fThumbRXf = (1 - a) + fThumbRXf + a*fThumbRX;
		fThumbRYf = (1 - a) + fThumbRYf + a*fThumbRY;

		if ((fThumbLX > 0) & (fThumbLY > 0)) {
			roState = pp;
			tRo = 1.0;
		}

		if (tRo > 0.0) {
			tRo = tRo - T;
			if (roState == np) roState = pp;
			if ((fThumbLX > 0) & (fThumbLY <= 0) & (roState == pp)) roState = pn;

			if ((fThumbLX <= 0) & (fThumbLY < 0) & (roState == pn)) roState = nn;

			if ((fThumbLX < 0) & (fThumbLY >= 0) & (roState == nn)) roState = np;
		}
		else
			tRo = pp;

		if (tLR > 0) tLR -= T;
		else sLR(0.0, 0.0);
		if (tRR > 0) tRR -= T;
		else sRR(0.0, 0.0);

		EscribeMando();
	}
}
