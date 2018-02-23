//Código base para generar una ventana

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE


#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
	//Registra la clase de la ventana
	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	//Crea la ventana
	HWND hwnd = CreateWindowEx(
		0,  //Estilos opcionales de la ventana
		CLASS_NAME,  //Clase de la ventana
		L"Learn to Program Windows",  //texto de la ventana
		//WS_OVERLAPPEDWINDOW, //Estilo de la ventana
		(WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX),
		//Tamaño y posición
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,  //Ventana madre
		NULL,  //Menu
		hInstance,  //Instance handle
		NULL   //Datos adicionales de la aplicación
	);
	if (hwnd == NULL) {
		return 0;
	}

	ShowWindow(hwnd, SW_MAXIMIZE);

	//Bucle de mensajes
	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) 
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT: 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 4));

		EndPaint(hwnd, &ps);
		return 0;
	}
	
	case WM_CLOSE: {
		if (MessageBox(hwnd, L"Really quit?", L"My application",
			MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		// Else: User canceled. Do nothing.
		return 0;
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

