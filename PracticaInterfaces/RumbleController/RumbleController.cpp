#include "HIDXbox.h"
#include <algorithm>

#define T 10 //ms para actualizar
#define TARGET_XBOX360
#ifdef TARGET_XBOX360
HIDXBox Control(T);
#elif defined(TARGET_PS3)
HIDPs Control(T);
#elif defined(TARGET_WII)
HIDWii Control(T);
#endif

HWND hWnd, hWndAnt;
void GeneraEfectos(HIDXBox* Control);

VOID CALLBACK TimerCallback() {
	Control.Actualiza();
	GeneraEfectos(&Control);
}

void GeneraEfectos(HIDXBox* Control) {
	POINT pt, pt0;

	GetCursorPos(&pt);
	if ((fabs(Control->gLJX()) > 0.05) | (fabs(Control->gLJY()) > 0.05)) {
		pt.x += 20 * Control->gLJX();
		pt.y -= 20 * Control->gLJY();
		SetCursorPos(pt.x, pt.y);
	}

	if ((fabs(Control->gRJXf()) > 0.05) | (fabs(Control->gRJYf()) > 0.05)) {
		pt.x += 20 * Control->gRJXf();
		pt.y -= 20 * Control->gRJYf();
		SetCursorPos(pt.x, pt.y);
	}

	if (Control->BD(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		mouse_event(MOUSEEVENTF_LEFTDOWN, pt.x, pt.y, 0, NULL);
	}

	if (Control->BU(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
		mouse_event(MOUSEEVENTF_LEFTUP, pt.x, pt.y, 0, NULL);
	}

	if (Control->BD(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		mouse_event(MOUSEEVENTF_RIGHTDOWN, pt.x, pt.y, 0, NULL);
	}

	if (Control->BU(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
		mouse_event(MOUSEEVENTF_RIGHTUP, pt.x, pt.y, 0, NULL);
	}

	if (Control->BD(XINPUT_GAMEPAD_X)) {
		keybd_event(VK_HOME, 0x24, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_X)) {
		keybd_event(VK_HOME, 0x24, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_B)) {
		keybd_event(VK_END, 0x23, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_B)) {
		keybd_event(VK_END, 0x23, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_Y)) {
		keybd_event(VK_PRIOR, 0x21, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_Y)) {
		keybd_event(VK_PRIOR, 0x21, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_A)) {
		keybd_event(VK_NEXT, 0x22, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_A)) {
		keybd_event(VK_NEXT, 0x22, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_BACK)) {
		keybd_event(VK_ESCAPE, 0x1B, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_BACK)) {
		keybd_event(VK_ESCAPE, 0x1B, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_START)) {
		keybd_event(VK_RETURN, 0x0D, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_START)) {
		keybd_event(VK_RETURN, 0x0D, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_DPAD_UP)) {
		keybd_event(VK_UP, 0x26, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_DPAD_UP)) {
		keybd_event(VK_UP, 0x26, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_DPAD_LEFT)) {
		keybd_event(VK_LEFT, 0x25, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_DPAD_LEFT)) {
		keybd_event(VK_LEFT, 0x25, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_DPAD_DOWN)) {
		keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_DPAD_DOWN)) {
		keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(XINPUT_GAMEPAD_DPAD_RIGHT)) {
		keybd_event(VK_RIGHT, 0x28, KEYEVENTF_EXTENDEDKEY | 0, 0);
	}

	if (Control->BU(XINPUT_GAMEPAD_DPAD_DOWN)) {
		keybd_event(VK_DOWN, 0x28, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
	}

	if (Control->BD(0XFFFF))
		Control->sRR(1, 0.1);

	hWnd = GetForegroundWindow();
	if (Control->GRLJ())
		ShowWindow(hWnd, SW_MINIMIZE);
	if (hWnd != hWndAnt)
		Control->sLR(1, 0.2);

}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
	Control.update();
	UINT_PTR ptimerxbox;
	ptimerxbox = SetTimer(NULL, NULL, T, (TIMERPROC)TimerCallback);
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//callTimer(NULL, ptimerxbox);
	return 0;

}

