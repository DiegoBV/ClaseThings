#include <windows.h>
#include "basewin.h"
#include "Scene.h"
#pragma comment(lib, "d2d1")
#include <windowsx.h>
#include <algorithm>
#include <string>


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

class MainWindow : public BaseWindow<MainWindow>
{
	Scene   Escena;			//Objeto que gestiona la Escena
	RECT	AreaCliente;	//Area Cliente
	UINT_PTR Timer;			//Timer

	int   OnCreate();
	void    OnDestroy();
	void    OnPaint();
	void    OnResize();
	void    OnTime();
	enum EditionMode { SelectMode, DrawMode, DragMode, NormalMode };
	ID2D1HwndRenderTarget *pRenderTarget;
	D2D1_POINT_2F ptMouse;
	MouseTrackEvents mouseTrack;
	double IDT_TIMER;
	TIMERPROC MyTimerProc;
	void setMode(EditionMode id) { modo = id; };

	void changeCursor();
	EditionMode modo;

public:
	MainWindow() : ptMouse(D2D1::Point2F()) {}
	PCWSTR ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void MainWindow::DrawClockHand(float fHandLength, float fAngle, float
		fStrokeWidth);
	void MainWindow::RenderScene();
	void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
	void OnLButtonUp();
	void OnMouseMove(int pixelX, int pixelY, DWORD flags);
};


int MainWindow::OnCreate()
{
	GetClientRect(m_hwnd, &AreaCliente);
	if (FAILED(Escena.CreaFactoria()))
	{
		return -1;  // Fail CreateWindowEx.
	}
	//Establezcpo un Timer T=1s; 
	Timer = SetTimer(m_hwnd, 0, 1000, (TIMERPROC)NULL);
	return 0;
}

void MainWindow::OnDestroy()
{
	Escena.DiscardGraphicsResources();
	Escena.LiberaFactoria();
	KillTimer(m_hwnd, Timer);
	PostQuitMessage(0);
}

void MainWindow::OnPaint()
{
	if (SUCCEEDED(Escena.CreateGraphicsResources(m_hwnd, AreaCliente)))
	{
		OnResize();
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);
		Escena.RenderScene();
		EndPaint(m_hwnd, &ps);
	}
}

void MainWindow::OnResize()
{
	if (Escena.pRenderTarget != NULL)
	{
		GetClientRect(m_hwnd, &AreaCliente);
		Escena.CalculateLayout(AreaCliente);
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::OnTime()
{
	SYSTEMTIME	time;
	GetLocalTime(&time);		
	//Actualizo el tiempo de la escena
	Escena.Actualizar(time.wHour,time.wMinute, time.wSecond);
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
			D2D1_FACTORY_TYPE_SINGLE_THREADED, &Escena.pFactory)))
		{
			return -1; // Fail CreateWindowEx.
		}
		Timer = SetTimer(m_hwnd, 0, 1000, (TIMERPROC)NULL);
		DPIScale::Initialize(Escena.pFactory);
		return 0;
	case WM_DESTROY:
		Escena.DiscardGraphicsResources();
		KillTimer(m_hwnd, Timer);
		SafeRelease(&Escena.pFactory);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnPaint();
		return 0;
	case WM_TIMER: // process the 1-second timer
		OnTime();
		PostMessage(m_hwnd, WM_PAINT, NULL, NULL);
		return 0;
	case WM_SIZE:
		OnResize();
		return 0;

	case WM_LBUTTONDOWN:
	{
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
		if (DragDetect(m_hwnd, pt))
		{
			OnLButtonDown(pt.x, pt.y, (DWORD)wParam);
		}
	}
	return 0;
	case WM_RBUTTONDOWN:
		Escena.changeColour(m_hwnd);
		return 0;
	case WM_LBUTTONUP:
		OnLButtonUp();
		return 0;

	case WM_MOUSEMOVE:
		changeCursor();
		if (Escena.estaEncima(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))) {
			Escena.isOver = true;
			EditionMode newMode = DragMode; setMode(newMode);
		}
		else {
			Escena.isOver = false;
			if (modo != DrawMode) {
				EditionMode newMode = NormalMode; setMode(newMode);
			}
		}
		OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
		PostMessage(m_hwnd, WM_PAINT, NULL, NULL);
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
			Escena.stop = !Escena.stop;
		}
		else if (GetKeyState(VK_ESCAPE))
		{
			Escena.DiscardGraphicsResources();
			SafeRelease(&Escena.pFactory);
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
		return 0;
	}

	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);

}


void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{

	SetCapture(m_hwnd);
	if (modo != DragMode) {
		Escena.newEllipse.point = ptMouse = DPIScale::PixelsToDips(pixelX, pixelY);
		Escena.newEllipse.radiusX = Escena.newEllipse.radiusY = 1.0f;
	}
	InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
	if (flags & MK_LBUTTON)
	{
		const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);
		if (modo != DragMode) {
			const float width = (dips.x - ptMouse.x) / 2;
			const float height = (dips.y - ptMouse.y) / 2;
			const float x1 = ptMouse.x + width;
			const float y1 = ptMouse.y + height;
			Escena.newEllipse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);
			InvalidateRect(m_hwnd, NULL, FALSE);
		}
		else {
			Escena.newEllipse.point = ptMouse = dips;
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		}
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


void MainWindow::changeCursor() {
	//if enuim== click
	if (modo == DragMode)
		SetCursor(LoadCursor(NULL, IDC_HAND));
	else if (modo == DrawMode)
		SetCursor(LoadCursor(NULL, IDC_CROSS));
	else
		SetCursor(LoadCursor(NULL, IDC_ARROW));
}

