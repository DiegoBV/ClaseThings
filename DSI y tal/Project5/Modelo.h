#pragma once
class Modelo
{

public:
	//Modelo de Datos////////////////////////////
	float x, y, radio;								//Esfera
	float fHourAngle, fMinuteAngle, fSecondAngle;	//Agujas
													/////////////////////////////////////////////
	Modelo();
	~Modelo();
	void Actualizar(int horas, int minutos, int segundos);
};

