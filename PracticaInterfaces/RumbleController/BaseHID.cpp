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
		EscribeMando(); //Escribo en Mando el feedback
	}
}
