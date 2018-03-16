#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")
#include "basewin.h"
#include <windowsx.h>
#include <algorithm>
#include <string>

template <class T> void SafeRelease(T **ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class DPIScale
{
	static float scaleX;
	static float scaleY;
public:
	static void Initialize(ID2D1Factory *pFactory)
	{
		FLOAT dpiX, dpiY;
		pFactory->GetDesktopDpi(&dpiX, &dpiY);
		scaleX = dpiX / 96.0f;
		scaleY = dpiY / 96.0f;
	}
	template <typename T>
	static D2D1_POINT_2F PixelsToDips(T x, T y)
	{
		return D2D1::Point2F(static_cast<float>(x) / scaleX,
			static_cast<float>(y) / scaleY);
	}
};

float DPIScale::scaleX = 1.0f;
float DPIScale::scaleY = 1.0f;

class MouseTrackEvents
{
	bool m_bMouseTracking;
public:
	MouseTrackEvents() : m_bMouseTracking(false)
	{
	}

	void OnMouseMove(HWND hwnd)
	{
		if (!m_bMouseTracking)
		{
			// Enable mouse tracking.
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = hwnd;
			tme.dwFlags = TME_HOVER | TME_LEAVE;
			tme.dwHoverTime = HOVER_DEFAULT;
			TrackMouseEvent(&tme);
			m_bMouseTracking = true;
		}
	}
	void Reset(HWND hwnd)
	{
		m_bMouseTracking = false;
	}
};

class MainWindow : public BaseWindow<MainWindow>
{
	enum EditionMode { SelectMode, DrawMode, DragMode, NormalMode };
	ID2D1Factory *pFactory;
	ID2D1HwndRenderTarget *pRenderTarget;
	ID2D1SolidColorBrush *pBrush;
	D2D1_ELLIPSE ellipse;
	D2D1_ELLIPSE newEllipse;
	ID2D1SolidColorBrush *pStroke;
	ID2D1SolidColorBrush *pFill;
	D2D1_POINT_2F ptMouse;
	MouseTrackEvents mouseTrack;
	bool stop = false;
	double IDT_TIMER;
	TIMERPROC MyTimerProc;
	void CalculateLayout();
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();
	void setMode(EditionMode id) { modo = id; };
	bool estaEncima(int pixelX, int pixelY);
	void changeCursor();
	void changeColour();
	float fHourAngle;
	float fMinuteAngle;
	float fSecondAngle;
	EditionMode modo;
	bool isOver = false;

public:
	MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL),
		ellipse(D2D1::Ellipse(D2D1::Point2F(), 0, 0)),
		ptMouse(D2D1::Point2F())
	{
	}
	PCWSTR ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void MainWindow::DrawClockHand(float fHandLength, float fAngle, float
		fStrokeWidth);
	void MainWindow::RenderScene();
	void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void OnLButtonUp();
	void OnMouseMove(int pixelX, int pixelY, DWORD flags);

};

// Recalculate drawing layout when the size of the window changes.

void MainWindow::DrawClockHand(float fHandLength, float fAngle, float
	fStrokeWidth)
{
	pRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Rotation(fAngle, ellipse.point)
		);
	// endPoint defines one end of the hand.
	D2D_POINT_2F endPoint = D2D1::Point2F(
		ellipse.point.x,
		ellipse.point.y - (ellipse.radiusY * fHandLength)
		);
	// Draw a line from the center of the ellipse to endPoint.
	pRenderTarget->DrawLine(
		ellipse.point, endPoint, pStroke, fStrokeWidth);
}

void MainWindow::RenderScene()
{
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	pRenderTarget->FillEllipse(ellipse, pBrush);
	pRenderTarget->DrawEllipse(ellipse, pStroke);
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
}

void MainWindow::CalculateLayout()
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();
		const float x = size.width / 2;
		const float y = size.height / 2;
		const float radius = min(x, y);
		ellipse = D2D1::Ellipse(D2D1::Point2F(x/8, y/8), radius/8, radius/8);
	}
}
HRESULT MainWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);
		SetTimer(m_hwnd, // handle to main window
			IDT_TIMER, // timer identifier
			1000, //1-second interval
			(TIMERPROC)MyTimerProc); // timer callback
		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

			const D2D1_COLOR_F color1 = D2D1::ColorF(0.0f, 0.0f, 0.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color1, &pStroke);

			const D2D1_COLOR_F color2 = D2D1::ColorF(1.0f, 1.0f, 1.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color2, &pFill);

			if (SUCCEEDED(hr))
			{
				CalculateLayout();
			}
		}
	}
	return hr;
}
void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrush);
	SafeRelease(&pStroke);
	SafeRelease(&pFill);
}
void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();
		/*pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
		pRenderTarget->FillEllipse(ellipse, pBrush);*/
		RenderScene();
		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}
void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	MainWindow win;
	if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}
	ShowWindow(win.Window(), nCmdShow);
	// Run the message loop.
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(
			D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
		{
			return -1; // Fail CreateWindowEx.
		}
		DPIScale::Initialize(pFactory);
		return 0;
	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnPaint();
		return 0;
	case WM_TIMER: // process the 1-second timer
		PostMessage(m_hwnd, WM_PAINT, NULL, NULL);
		return 0;
	case WM_SIZE:
		Resize();
		return 0;

	case WM_LBUTTONDOWN:
	{	
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		if (DragDetect(m_hwnd, pt))
		{
			OnLButtonDown(pt.x, pt.y, (DWORD)wParam);
			EditionMode newMode = DrawMode;
			setMode(newMode);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
		changeColour();
		return 0;
	case WM_LBUTTONUP:
		OnLButtonUp();
		return 0;

	case WM_MOUSEMOVE:
		changeCursor();
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		mouseTrack.OnMouseMove(m_hwnd);
		if (estaEncima(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))){
			isOver = true;
			EditionMode newMode = SelectMode; setMode(newMode);
		}
		else{
			isOver = false;
			if (modo != DrawMode){
				EditionMode newMode = NormalMode; setMode(newMode);
			}
		}
		return 0;

	case WM_MOUSELEAVE:
		// TODO: Handle the mouse-leave message.
		mouseTrack.Reset(m_hwnd);
		return 0;

	case WM_MOUSEHOVER:
		// TODO: Handle the mouse-hover message.
		mouseTrack.Reset(m_hwnd);
		return 0;
	case WM_SYSKEYDOWN:
		//printf(uMsg, L"WM_SYSKEYDOWN: 0x%x\n", wParam);
		//OutputDebugString(uMsg);
		break;
	case WM_SYSCHAR:
		//swprintf_s(msg, L"WM_SYSCHAR: %c\n", (wchar_t)wParam);
		//OutputDebugString(uMsg);
		break;
	case WM_SYSKEYUP:
		//swprintf_s(msg, L"WM_SYSKEYUP: 0x%x\n", wParam);
		//OutputDebugString(msg);
		break;
	case WM_KEYDOWN:
		if (GetKeyState(VK_SPACE))
		{
			stop = !stop;
		}
		else if (GetKeyState(VK_ESCAPE))
		{
			DiscardGraphicsResources();
			SafeRelease(&pFactory);
			PostQuitMessage(0);
		}
		//swprintf_s(msg, L"WM_KEYDOWN: 0x%x\n", wParam);
		//OutputDebugString(msg);
		break;
	case WM_KEYUP:
		//swprintf_s(msg, L"WM_KEYUP: 0x%x\n", wParam);
		//OutputDebugString(msg);
		break;
	case WM_CHAR:
		//swprintf_s(msg, L"WM_CHAR: %c\n", (wchar_t)wParam);
		//OutputDebugString(msg);
		break;
	case WM_COMMAND:
		/*switch (LOWORD(wParam))
		{
		case ID_DRAW_MODE:
			SetMode(DrawMode);
			break;
		case ID_SELECT_MODE:
			SetMode(SelectMode);
			break;
		case ID_TOGGLE_MODE:
			if (mode == DrawMode)
			{
				SetMode(SelectMode);
			}
			else
			{
				SetMode(DrawMode);
			}
			break;
		}*/
		return 0;
		/* Handle other messages (not shown) */
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{

	SetCapture(m_hwnd);
	newEllipse.point = ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
	newEllipse.radiusX = newEllipse.radiusY = 1.0f;
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	if (flags & MK_LBUTTON)
	{
		const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);
		const float width = (dips.x - ptMouse.x) / 2;
		const float height = (dips.y - ptMouse.y) / 2;
		const float x1 = ptMouse.x + width;
		const float y1 = ptMouse.y + height;
		newEllipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::OnLButtonUp()
{
	ReleaseCapture();
	EditionMode newMode = NormalMode;
	setMode(newMode);
}

UINT GetMouseHoverTime()
{
	UINT msec;
	if (SystemParametersInfo(SPI_GETMOUSEHOVERTIME, 0, &msec, 0))
	{
		return msec;
	}
	else
	{
		return 0;
	}
}

bool MainWindow::estaEncima(int pixelX, int pixelY){
	double local = (pow(pixelX - newEllipse.point.x, 2) / pow(newEllipse.radiusX, 2)) +
		(pow(pixelY - newEllipse.point.y, 2) / pow(newEllipse.radiusY, 2));
	/*if (local <= 1.0){
		EditionMode newMode = SelectMode;
		setMode(newMode);
	}
	else{
		EditionMode newMode = NormalMode;
		setMode(newMode);
	}*/
	return local <= 1.0;
}

void MainWindow::changeCursor(){
	//if enuim== click
	if (modo == SelectMode)
		SetCursor(LoadCursor(NULL, IDC_HAND));
	else if (modo == DrawMode)
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void MainWindow::changeColour(){
	if (isOver){
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
			DWORD KK  = cc.rgbResult;
			D2D1_COLOR_F color2 = D2D1::ColorF((float)GetRValue(cc.rgbResult) / 255, 
				(float)GetGValue(cc.rgbResult) / 255, (float)GetBValue(cc.rgbResult) / 255);
			color2.a = 1;
			pFill->SetColor(color2);
			//En cc.rgbResult tenemos el color seleccionado
			//Utilizarlo para configurar nuestra brocha
			//Es necesario transformarlo al formato de color de D2D
		}
	}
}
