#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#define WND_ID 100
#define WND_FIRSTCHILD_ID 101
#define WND_SECONDCHILD_ID 102

#include <Windows.h>
#include <CommCtrl.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES;  // Enables a set of common controls.
	InitCommonControlsEx(&icex);

	WNDCLASSW wc = {};
	wc.lpszClassName = L"WndClass";
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;

	WNDCLASSW wcChild = {};
	wcChild.lpszClassName = L"ChildWndClass";
	wcChild.lpfnWndProc = ChildWindowProc;
	wcChild.hInstance = hInstance;

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK);
		return FALSE;
	}
	if (!RegisterClass(&wcChild))
	{
		MessageBox(NULL, L"Failed To Register The Child Window Class.", L"ERROR", MB_OK);
		return FALSE;
	}

	HWND hwnd = CreateWindowExW(
		0,                          // Extended Style For The Window
		L"WndClass",             // Class Name
		L"Title",                              // Window Title
		WS_OVERLAPPEDWINDOW,                    // Required Window Style
		CW_USEDEFAULT, CW_USEDEFAULT, 
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,                               // No Parent Window
		NULL,                               // No Menu
		hInstance,                          // Instance
		NULL);								// Dont Pass Anything To WM_CREATE
	

	if (!hwnd)
	{
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK);
		return FALSE;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//HWND hwndButton = CreateWindowW(
	//	L"BUTTON",  // Predefined class; Unicode assumed 
	//	L"OK",      // Button text 
	//	WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
	//	10,         // x position 
	//	10,         // y position 
	//	100,        // Button width
	//	100,        // Button height
	//	hwnd,     // Parent window
	//	(HMENU)1,       // No menu.
	//	hInstance,
	//	NULL);      // Pointer not needed.


		

	//BOOL shouldClose = FALSE;

	MSG msg;

	while (GetMessageW(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		HWND hwndChild1, hwndChild2;
		hwndChild1 = CreateWindowExW(0, L"ChildWndClass");

		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:	
		hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);	
		return 0;
	/*case WM_COMMAND:
	{

		if (LOWORD(wParam) == 1)
		{
			MessageBoxW(NULL, L"Button 1 Click", L"None", MB_OK);
		}
		if (LOWORD(wParam) == 2)
		{
			MessageBoxW(NULL, L"Button 2 Click", L"None", MB_OK);
		}
		return 0;
	}*/
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


LRESULT CALLBACK ChildWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		return 0;
	}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}