#pragma once

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <glad/glad.h>

#include <Windows.h>
#include <string>

#include <App.hpp>

namespace Window
{
	const std::wstring WND_CLASS_NAME = L"WndClass";
	
	extern BOOL done;
	extern WNDCLASSW wc;
	extern HWND hwnd;
	extern HDC hdc;
	extern HGLRC hrc;

	LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wp, LPARAM lp);
	BOOL createWindow(wchar_t* title = L"Demo Program", int width = 800, int height = 600);

	namespace priv
	{

	}

}