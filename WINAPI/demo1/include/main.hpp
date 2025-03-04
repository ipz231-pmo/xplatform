#include <string>
#include <Windows.h>



const std::wstring WND_CLASS_NAME = L"WndClass";
const std::string PROJECT_DIRECTORY = "../";
const std::string SHADERS_DIRECTORY = "../shaders/";


extern HINSTANCE hInstance;
extern BOOL shouldClose;
extern WNDCLASSW wc;
extern HWND hwnd;
extern HDC hdc;
extern HGLRC hrc;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp);
BOOL createWindow(wchar_t* title = L"Demo Program", int width = 800, int height = 600);