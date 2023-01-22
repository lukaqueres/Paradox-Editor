#include "Window.h"
#include "../Common/ErrorBox.h"
#include "../Common/Utils.h"

constexpr const wchar_t* Window::s_ClassName;
unsigned int Window::s_WindowCount = 0;

Window::Window(int width, int height, const char* title)
	: m_Handle(nullptr), m_Width(width), m_Height(height), m_Title(title)
{
	//We want to create window class only for the first window.
	if (s_WindowCount == 0)
	{
		WNDCLASSEX wc = {};
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = SetupWindowProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = s_ClassName;
		wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

		if (RegisterClassEx(&wc) == 0)
		{
			ErrorBox::Show(L"Failed to register window class");
		}
	}
	
	RECT windowRect = {0, 0, m_Width, m_Height};
	AdjustWindowRect(&windowRect, WS_CAPTION | WS_SYSMENU, FALSE);

	m_Handle = CreateWindowEx(0, s_ClassName, StringUtils::ToWide(m_Title).c_str(), WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, GetModuleHandle(nullptr), this);

	if (!m_Handle)
	{
		ErrorBox::Show(L"Failed to create a window");
	}

	ShowWindow(m_Handle, SW_NORMAL);
	UpdateWindow(m_Handle);
	
	s_WindowCount += 1;
}

Window::~Window()
{
	DestroyWindow(m_Handle);
	s_WindowCount -= 1;

	if (s_WindowCount == 0)
		UnregisterClass(s_ClassName, GetModuleHandle(nullptr));
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return (int)msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

LRESULT Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::SetupWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const createStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const window = static_cast<Window*>(createStruct->lpCreateParams);

		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::WindowProcThunk));

		return window->WindowProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::WindowProcThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* const window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	return window->WindowProc(hwnd, msg, wParam, lParam);
}