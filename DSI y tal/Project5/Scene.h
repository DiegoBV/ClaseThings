#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "Modelo.h"
#include <algorithm>

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class Scene: public Modelo
{
public:
	Scene();
	~Scene();
	ID2D1Factory            *pFactory;
	ID2D1SolidColorBrush    *pBrush; //color de Esfera
	ID2D1SolidColorBrush    *pStroke; //color de flechas
	ID2D1HwndRenderTarget   *pRenderTarget;
	D2D1_ELLIPSE             ellipse;
	D2D1_ELLIPSE newEllipse;
	ID2D1SolidColorBrush *pFill;

	float fHourAngle;
	float fMinuteAngle;
	void changeColour(HWND m_hwnd);
	bool isOver = false;
	float fSecondAngle;
	

	//Manejar recursos gráficos
	HRESULT CreaFactoria();
	void	LiberaFactoria();
	HRESULT CreateGraphicsResources(HWND m_hwnd,RECT rc);
	void    DiscardGraphicsResources();
	
	//Layout y Dibujo
	void    CalculateLayout(RECT rc);
	void	DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth);
	void	DrawEsfera();
	void	RenderScene(bool stop);
	bool estaEncima(int pixelX, int pixelY);

};

