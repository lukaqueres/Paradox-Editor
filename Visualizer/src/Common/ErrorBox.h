#pragma once
#include <Windows.h>

class ErrorBox
{
public:
	static void Show(const wchar_t* message)
	{
		MessageBox(nullptr, message, L"Error", MB_OK | MB_ICONERROR);
	}
};