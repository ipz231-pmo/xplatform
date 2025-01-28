#include "Window.hpp"

BOOL		Window::done		= false;
WNDCLASSW	Window::wc			= { };
HWND		Window::hwnd		= NULL;
HDC			Window::hdc			= NULL;
HGLRC		Window::hrc			= NULL;


LRESULT CALLBACK Window::WndProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC HDC = BeginPaint(hwnd, &ps);

		FillRect(HDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProcW(hwnd, uMsg, wp, lp);
}


BOOL Window::createWindow(wchar_t* title, int width, int height)
{
	DWORD       dwExStyle;              // Window Extended Style
	DWORD       dwStyle;                // Window Style
	RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;            // Set Left Value To 0
	WindowRect.right = (long)width;       // Set Right Value To Requested Width
	WindowRect.top = (long)0;             // Set Top Value To 0
	WindowRect.bottom = (long)height;     // Set Bottom Value To Requested Height


	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;			// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = WndProc;								// WndProc Handles Messages
	wc.cbClsExtra = 0;										// No Extra Window Data
	wc.cbWndExtra = 0;										// No Extra Window Data
	wc.hInstance = App::hInstance;							// Set The Instance
	wc.hIcon = LoadIconW(NULL, IDI_WINLOGO);				// Load The Default Icon
	wc.hCursor = LoadCursorW(NULL, IDC_ARROW);				// Load The Arrow Pointer
	wc.hbrBackground = NULL;								// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = WND_CLASS_NAME.c_str();				// Set The Class Name

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, L"Failed To Register The Window Class.", L"ERROR", MB_OK);
		return FALSE;
	}


	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;           // Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;                            // Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);     // Adjust Window To True Requested Size


	// Create The Window
	if (!(hwnd = CreateWindowExW(
		dwExStyle,                          // Extended Style For The Window
		WND_CLASS_NAME.c_str(),             // Class Name
		title,                              // Window Title
		dwStyle |                           // Defined Window Style
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN,                    // Required Window Style
		0, 0,                               // Window Position
		WindowRect.right - WindowRect.left, // Calculate Window Width
		WindowRect.bottom - WindowRect.top, // Calculate Window Height
		NULL,                               // No Parent Window
		NULL,                               // No Menu
		App::hInstance,                          // Instance
		NULL)								// Dont Pass Anything To WM_CREATE
		))                             
	{
		MessageBox(NULL, L"Window Creation Error.", L"ERROR", MB_OK);
		return FALSE;                               // Return FALSE
	}

	PIXELFORMATDESCRIPTOR pfd =              // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),              // Size Of This Pixel Format Descriptor
		1,                                          // Version Number
		PFD_DRAW_TO_WINDOW |                        // Format Must Support Window
		PFD_SUPPORT_OPENGL |                        // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,                           // Must Support Double Buffering
		PFD_TYPE_RGBA,                              // Request An RGBA Format
		16,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,                           // Color Bits Ignored
		0,                                          // No Alpha Buffer
		0,                                          // Shift Bit Ignored
		0,                                          // No Accumulation Buffer
		0, 0, 0, 0,                                 // Accumulation Bits Ignored
		24,                                         // 16Bit Z-Buffer (Depth Buffer)  
		8,                                          // 8bit Stencil Buffer
		0,                                          // No Auxiliary Buffer
		PFD_MAIN_PLANE,                             // Main Drawing Layer
		0,                                          // Reserved
		0, 0, 0                                     // Layer Masks Ignored		
	};


	if (!(hdc = GetDC(hwnd)))                         // Did We Get A Device Context?
	{
		MessageBox(NULL, L"Can't Create A GL Device Context.", L"ERROR", MB_OK);
		return FALSE;
	}

	int choosedPixelFormat;
	if (!(choosedPixelFormat = ChoosePixelFormat(hdc, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		MessageBox(NULL, L"Can't Find A Suitable PixelFormat.", L"ERROR", MB_OK);
		return FALSE;
	}

	if (!SetPixelFormat(hdc, choosedPixelFormat, &pfd))       // Are We Able To Set The Pixel Format?
	{
		MessageBox(NULL, L"Can't Set The PixelFormat.", L"ERROR", MB_OK);
		return FALSE;
	}


	if (!(hrc = wglCreateContext(hdc)))               // Are We Able To Get A Rendering Context?
	{
		MessageBox(NULL, L"Can't Create A GL Rendering Context.", L"ERROR", MB_OK);
		return FALSE;
	}

	if (!wglMakeCurrent(hdc, hrc))                    // Try To Activate The Rendering Context
	{
		MessageBox(NULL, L"Can't Activate The GL Rendering Context.", L"ERROR", MB_OK);
		return FALSE;
	}

	if (!gladLoadGL())
	{
		MessageBox(NULL, L"Cannot load GLAD.", L"ERROR", MB_OK);
		return FALSE;
	}

	ShowWindow(hwnd, SW_SHOW);                       // Show The Window
	SetForegroundWindow(hwnd);                      // Slightly Higher Priority
	SetFocus(hwnd);                                 // Sets Keyboard Focus To The Window

	return TRUE;
}
