#include "WindowClass.h"

WindowClass* m_Instance;
constexpr const char* m_ClassName;

WindowClass* WindowClass::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new WindowClass();
	}

	return m_Instance;
}

const wchar_t* WindowClass::GetName()
{
	return m_ClassName;
}

bool WindowClass::Register(WNDPROC wndProc)
{
	if (WindowCount != 0)
	{
		return true;
	}

	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = wndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = m_ClassName;
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	//RegisterClassEx returns 0 on failure.
	if (RegisterClassEx(&wc) == 0)
	{
		//TODO: Error logging.
		return false;
	}

	return true;
}

bool WindowClass::Unregister()
{
	if (WindowCount != 0)
	{
		return true;
	}

	if (UnregisterClass(m_ClassName, GetModuleHandle(nullptr)) == 0)
	{
		//TODO: Error logging.
		return false;
	}

	return true;
}
