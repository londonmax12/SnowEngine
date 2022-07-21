#include "snowpch.h"
#ifdef SNOW_PLATFORM_WINDOWS
#include "src/Window/Window.h"
#include "src/Event/ApplicationEvent.h"
#include "src/Application/Application.h"

#include <windows.h>
#include <windowsx.h>

namespace Snow {
	struct InternalState {
		HINSTANCE instance;
		HWND hwnd;
	};

	Window::Window(WindowSpecification spec, PlatformState* state)
	{
		m_X = spec.x;
		m_Y = spec.y;
		m_Width = spec.width;
		m_Height = spec.height;
		m_ApplicationName = spec.windowName;

		m_PlatformState = state;

		Init(state);
	}

	Window::~Window()
	{
		InternalState* state = (InternalState*)m_PlatformState->internalState;

		if (state->hwnd) {
			DestroyWindow(state->hwnd);
			state->hwnd = 0;
		}
	}
	LRESULT win32ProcessMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_ERASEBKGND:
		{
			return 1;
		}
		case WM_CLOSE:
		{
			WindowCloseEvent ev;
			Application::GetInstance()->OnEvent(ev);
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_SIZE:
		{
			RECT r;
			GetClientRect(hwnd, &r);
			int w = r.right - r.left;
			int h = r.bottom - r.top;
			break;
		}
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			bool pressed(msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
			break;
		}
		case WM_MOUSEMOVE:
		{
			int x = GET_X_LPARAM(lParam);
			int y = GET_Y_LPARAM(lParam);
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int delta = GET_WHEEL_DELTA_WPARAM(wParam);
			if (delta != 0) {
				delta = delta < 0 ? -1 : 1;
			}
		}
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
		{
			bool pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
			break;
		}
		}
		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}

	bool Window::Init(PlatformState* platformState)
	{
		platformState->internalState = malloc(sizeof(InternalState));
		InternalState* state = (InternalState*)platformState->internalState;
		state->instance = GetModuleHandleA(0);

		HICON icon = LoadIcon(state->instance, IDI_APPLICATION);
		WNDCLASSA wc;
		memset(&wc, 0, sizeof(wc));
		wc.style = CS_DBLCLKS;
		wc.lpfnWndProc = win32ProcessMessage;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = state->instance;
		wc.hIcon = icon;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszClassName = "snow_window_class";

		if (!RegisterClassA(&wc)) {
			SNOW_ERROR("Failed to start Win32 window class");
			return false;
		}

		int clientX = m_X;
		int clientY = m_Y;
		int clientW = m_Width;
		int clientH = m_Height;

		int windowX = clientX;
		int windowY = clientY;
		int windowH = clientH;
		int windowW = clientW;

		int windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		int windowExStyle = WS_EX_APPWINDOW;

		windowStyle |= WS_MAXIMIZEBOX;
		windowStyle |= WS_MINIMIZEBOX;
		windowStyle |= WS_THICKFRAME;

		RECT borderRect = { 0,0,0,0 };
		AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);

		windowX += borderRect.left;
		windowY += borderRect.top;

		windowW += borderRect.right - borderRect.left;
		windowH += borderRect.bottom - borderRect.top;

		HWND handle = CreateWindowExA(windowExStyle, "snow_window_class", m_ApplicationName, windowStyle, windowX, windowY, windowW, windowH, 0, 0, state->instance, 0);
		if (!handle) {
			SNOW_FATAL("Window creation failed");
			return false;
		}
		state->hwnd = handle;

		bool shouldActivate = true;
		int showWindowCommandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;

		ShowWindow(state->hwnd, showWindowCommandFlags);

		platform_Init();

		m_PlatformState = platformState;

		return true;
	}
}
#endif