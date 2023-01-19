#pragma once
#include <Windows.h>

//Helper class for handling winapi window class registration.
class WindowClass
{
public:
	//Register/unregister window class only if this counter is equal to 0.
	unsigned int WindowCount = 0;

	//Returns true if already window class is already registered
	bool Register(WNDPROC wndProc);
	bool Unregister();

	static WindowClass* GetInstance();
	static const wchar_t* GetName();
private:
	WindowClass() = default;

	static WindowClass* m_Instance;
	static constexpr const wchar_t* m_ClassName = L"MyWindowClass";
};