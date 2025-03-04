#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <glad/glad.h>

#include <Windows.h>

#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <time.h>

#include "main.hpp"
#include "Time.hpp"

#include <Shader.hpp>


float vertices[] =
{
	-0.5, -0.5, 0.1,
	0.5, -0.5, 0.1,
	0.5, 0.5, 0.1
};

#ifdef _DEBUG
void ShowDebugConsole() {
	AllocConsole();
	FILE* file;
	freopen_s(&file, "CONOUT$", "w", stdout);
	freopen_s(&file, "CONOUT$", "w", stderr);
	freopen_s(&file, "CONIN$", "r", stdin);
}
#endif // _DEBUG




int wWinMain(HINSTANCE hIns, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

#ifdef _DEBUG
	ShowDebugConsole();
#endif // DEBUG

	

	
	hInstance = hIns;


	DWORD       dwExStyle;              // Window Extended Style
	DWORD       dwStyle;                // Window Style
	RECT        WindowRect;             // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;            // Set Left Value To 0
	WindowRect.right = (long)800;       // Set Right Value To Requested Width
	WindowRect.top = (long)0;             // Set Top Value To 0
	WindowRect.bottom = (long)600;     // Set Bottom Value To Requested Height


	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;			// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = DefWindowProc;								// WndProc Handles Messages
	wc.cbClsExtra = 0;										// No Extra Window Data
	wc.cbWndExtra = 0;										// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
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
		L"title",                              // Window Title
		dwStyle |                           // Defined Window Style
		WS_CLIPSIBLINGS |                   // Required Window Style
		WS_CLIPCHILDREN,                    // Required Window Style
		0, 0,                               // Window Position
		WindowRect.right - WindowRect.left, // Calculate Window Width
		WindowRect.bottom - WindowRect.top, // Calculate Window Height
		NULL,                               // No Parent Window
		NULL,                               // No Menu
		hInstance,                          // Instance
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



	Shader shader(SHADERS_DIRECTORY + "1.vert", SHADERS_DIRECTORY + "1.frag");

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shader Input Params
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	MSG msg = { };


	while (!shouldClose)
	{
		Time::calcDeltaTime();

		while (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				shouldClose = TRUE;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		shader.bind();
		shader.setVec3("Color", glm::vec3(1.0, 1.0, 1.0));

		// Draw here
		glClearColor(0.5, 0, 0, 1.0);

		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SwapBuffers(hdc);
	}
	return 0;

}


HINSTANCE hInstance;
BOOL shouldClose;
WNDCLASSW wc;
HWND hwnd;
HDC hdc;
HGLRC hrc;