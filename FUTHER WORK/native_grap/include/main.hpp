#ifndef UNICODE
#define UNICODE
#endif  // !UNICODE




#include <windows.h>
#include <cstdio>
#include <string>



LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const std::string ASSETS_DIR = "..\\assets\\";
const std::string LOGS_DIR = "..\\logs\\";

