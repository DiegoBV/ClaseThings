#include "Scene.h"


Scene::Scene():pBrush(NULL), pRenderTarget(NULL), pFactory(NULL)

{
	
}


Scene::~Scene()
{
}


HRESULT Scene::CreaFactoria()
{
	return	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory);
}

void Scene::LiberaFactoria()
{
	SafeRelease(&pFactory);
}

void Scene::DrawClockHand(float fHandLength, float fAngle, float fStrokeWidth)
{
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(fAngle, ellipse.point));
	// endPoint defines one end of the hand.
	D2D_POINT_2F endPoint = D2D1::Point2F(ellipse.point.x,ellipse.point.y - (ellipse.radiusY * fHandLength));
	// Draw a line from the center of the ellipse to endPoint.
	pRenderTarget->DrawLine(ellipse.point, endPoint, pStroke, fStrokeWidth);
}

void Scene::DrawEsfera()
{
	ellipse = D2D1::Ellipse(D2D1::Point2F(x/8, y/8), radio/8, radio/8);
	pRenderTarget->FillEllipse(ellipse, pBrush);
	pRenderTarget->DrawEllipse(ellipse, pStroke);
}
void Scene::RenderScene()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	DrawEsfera();
	pRenderTarget->FillEllipse(newEllipse, pFill);
	pRenderTarget->DrawEllipse(newEllipse, pStroke);

	// Draw hands
	SYSTEMTIME time;
	GetLocalTime(&time);

	if (!stop) {
		fMinuteAngle = (360.0f / 12) * (time.wHour) +
			(time.wMinute * 0.5f);
		fMinuteAngle = (360.0f / 60) * (time.wMinute);
		fSecondAngle = (360.0f / 60) * (time.wSecond);

		// 60 minutes = 30 degrees, 1 minute = 0.5 degree
		DrawClockHand(0.6f, fHourAngle, 6);
		DrawClockHand(0.85f, fMinuteAngle, 4);
		DrawClockHand(0.90f, fSecondAngle, 3);
		// Restore the identity transformation.
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}
	else
	{
		// 60 minutes = 30 degrees, 1 minute = 0.5 degree
		DrawClockHand(0.6f, fHourAngle, 6);
		DrawClockHand(0.85f, fMinuteAngle, 4);
		DrawClockHand(0.90f, fSecondAngle, 3);
		// Restore the identity transformation.
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	}

	HRESULT hr = pRenderTarget->EndDraw();
	if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
	{
		DiscardGraphicsResources();
	}
}
// Recalculate drawing layout when the size of the window changes.

void Scene::CalculateLayout(RECT rc)
{
	D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
	if (pRenderTarget != NULL)
	{
		pRenderTarget->Resize(size);
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		x = size.width / 2;
		y = size.height / 2;
		radio = min(x, y);
	}
}

HRESULT Scene::CreateGraphicsResources(HWND m_hwnd,RECT rc)
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			const D2D1_COLOR_F color1 = D2D1::ColorF(0.0f, 0.0f, 0);
			hr = pRenderTarget->CreateSolidColorBrush(color1, &pStroke);

			const D2D1_COLOR_F color2 = D2D1::ColorF(1.0f, 1.0f, 1.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color2, &pFill);

			if (SUCCEEDED(hr))
			{
				CalculateLayout(rc);
			}
		}
	}
	return hr;
}

void Scene::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
	SafeRelease(&pStroke);
}

bool Scene::estaEncima(int pixelX, int pixelY) {
	double local = (pow(pixelX - newEllipse.point.x, 2) / pow(newEllipse.radiusX, 2)) +
		(pow(pixelY - newEllipse.point.y, 2) / pow(newEllipse.radiusY, 2));
	return local <= 1.0;
}


void Scene::changeColour(HWND m_hwnd) {
	if (isOver) {
		CHOOSECOLOR cc; // common dialog box structure
		static COLORREF acrCustClr[16]; // array of custom colors
		static DWORD rgbCurrent; // initial color selection
								 // Initialize CHOOSECOLOR
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = m_hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		if (ChooseColor(&cc) == TRUE)
		{
			DWORD KK = cc.rgbResult;
			D2D1_COLOR_F color2 = D2D1::ColorF((float)GetRValue(cc.rgbResult) / 255,
				(float)GetGValue(cc.rgbResult) / 255, (float)GetBValue(cc.rgbResult) / 255);
			color2.a = 1;
			pFill->SetColor(color2);
		}
	}
}
