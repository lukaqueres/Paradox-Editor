#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#define VISUALIZER_API __declspec(dllexport)

extern "C" VISUALIZER_API void ShowMessageBox()
{
	MessageBox(nullptr, L"DLL loaded properly", L"It's working!", MB_OK | MB_ICONINFORMATION);
}