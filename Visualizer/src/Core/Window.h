#pragma once
#include <Windows.h>
#include <optional>

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;

	static std::optional<int> ProcessMessages();

private:
	HWND m_Handle;
	int m_Width;
	int m_Height;
	const char* m_Title;

	static unsigned int s_WindowCount;
	static constexpr const wchar_t* s_ClassName = L"MyWindowClass";

	LRESULT WINAPI WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI SetupWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI WindowProcThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};