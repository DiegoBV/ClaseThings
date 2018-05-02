#pragma once
#include <windows.h>
#include <commdlg.h>
#include <XInput.h>
#include <basetsd.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "resource.h"

enum Rotation {pp, pn, nn, np};
class BaseHID
{
protected:
	//Entradas
	short wButtons; //Botones (Utilizo Codificación Xbox360)
	short wLastButtons; //Botones anteriores (Utilizo Codificación Xbox360)
	float fLeftTrigger, fRightTrigger; //[0.0,1.0]
	float fThumbLX = 0, fThumbLY = 0, fThumbRX = 0, fThumbRY = 0; //[-1.0,1.0]
	float fThumbLXf = 0, fThumbLYf = 0, fThumbRXf = 0, fThumbRYf = 0; //[-1.0,1.0] Filtrado
	float T; //Perido de actualización
	float a; //Cte.Tiempo Filtro
				   //Salidas
	float fLeftVibration, fRightVibration; //[0.0,1.0] Salida
	float tLR = 0.0; //Tiempo que queda de vibración en LR
	float tRR = 0.0; //Tiempo que queda de vibración en RR
					 //Gestos
	short wButtonsDown; //EventosDown Botones (Codificación Xbox360?)
	short wButtonsUp; //EventosUp Botones (Codificación Xbox360?)
					  //EstadosRotacion Ro; //Estado del gesto de rotación
	float tRo = 0.0; //Tiempo que queda para el gesto de rotación
					 //Funciones virtuales que se deben reimplementar para cada mando.

	float velX = 0.0;

	const double rotacionTime = 100;


	virtual bool LeeMando() = 0; //Lee estado del mando
	virtual void EscribeMando() = 0; //Escribe Feeback en mando
	virtual void Mando2HID() = 0; //Vuelca el estado del mando al HID
	Rotation roState;


public:
	bool bConected; //Mando Conectado
					//Gets & Sets
	bool gBU(WORD bit) { return true; }; //Estado del Boton codificado en bit
	float gLT() { return fLeftTrigger; }; //Left Triger [0,1]
	float gRT() { return fRightTrigger; }; //Right Triger [0,1]
	float gLJX() { return fThumbLX; }; //LeftJoyX [-1,1]
	float gLJY() { return fThumbLY; }; //LeftJoyY [-1,1]
	float gRJX() { return fThumbRX; }; //RightJoyX [-1,1]
	float gRJY() { return fThumbRY; }; //RightJoyY [-1,1]
	float gLJXf() { return fThumbLXf; }; //LeftJoyXfiltered [-1,1]
	float gLJYf() { return fThumbLYf; }; //LeftJoyYfiltered [-1,1]
	float gRJXf() { return fThumbRXf; }; //RightJoyXfiltered [-1,1]
	float gRJYf() { return fThumbRYf; }; //RigthJoyYfiltered [-1,1]
	void sLR(float cantidad, float tiempo) { fLeftVibration = cantidad; tLR = tiempo; }; //LeftRumble [0,1]: cantidad [0,1], tiempo [0,inf]
	void sRR(float cantidad, float tiempo) { fRightVibration = cantidad; tRR = tiempo; }; //RightRumble [0,1]: cantidad [0,1], tiempo [0,inf]
											//Gestos
	bool BD(WORD Bit) { return (wButtonsDown & Bit); }; //Boton Down codificado en Bit
	bool BU(WORD Bit) { return (wButtonsUp & Bit); }; //Boton Up codificado en Bit
	bool GRLJ() { if (roState == np) { roState = pp; return true; } else { return false; } }; //Gesto de Rotación del LeftJoy +  reset de la rotacion

	BaseHID(float t) //Constructor que recoge el periodo de muestreo
	{
		T = t / 1000; //Periodo de muestreo
		a = T / (0.1 + T); //Cte. de tiempo para filtros (depende de T)
		fThumbLX = 0;
	};
	BaseHID() {};
	~BaseHID() {};
	void Actualiza(); //Actualiza Mando2HID y HID2Mando.

};

