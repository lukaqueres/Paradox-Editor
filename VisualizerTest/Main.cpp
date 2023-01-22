#include <Visualizer.h>

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Window* window1 = new Window(800, 600, "Window 1");
	Window* window2 = new Window(500, 300, "Window 2");
	Window* window3 = new Window(100, 400, "Window 3");
	Window* window4 = new Window(800, 50, "LongBoii");

	while (true)
	{
		if (auto exitCode = Window::ProcessMessages())
		{
			delete window1;
			delete window2;
			delete window3;
			delete window4;
			return *exitCode;
		}
	}
}