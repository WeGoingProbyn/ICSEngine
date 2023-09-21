#include "Platform/PlatformWin32.h"
#include "Core/Events/EventHandler.h"

PlatformWin32::InstanceHandler PlatformWin32::InstanceHandler::m_InstanceHandle;

PlatformWin32::InstanceHandler::InstanceHandler() {
	m_Window = nullptr;
	m_Instance = GetModuleHandle(nullptr);
	WNDCLASSEX WindowClass = { 0 };
	WindowClass.cbClsExtra = 0;
	WindowClass.cbWndExtra = 0;
	WindowClass.hIcon = nullptr;
	WindowClass.style = CS_OWNDC;
	WindowClass.hCursor = nullptr;
	WindowClass.hIconSm = nullptr;
	WindowClass.lpszMenuName = nullptr;
	WindowClass.hbrBackground = nullptr;
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.hInstance = m_InstanceHandle.m_Instance;
	WindowClass.lpfnWndProc = DesignateObjectPointerToWindow;
	WindowClass.lpszClassName = (LPCWSTR)m_InstanceHandle.m_WindowName;

	RegisterClassEx(&WindowClass);
}

PlatformWin32::InstanceHandler::~InstanceHandler() { UnregisterClass((LPCWSTR)m_InstanceHandle.m_WindowName, m_InstanceHandle.m_Instance); }

PlatformWin32::PlatformWin32()
{
	// TODO: Maybe do this better
	m_Config.x = 0u;
	m_Config.y = 0u;
	m_Config.width = 1200u;
	m_Config.height = 720u;
	m_Config.name = L"ICS engine";

	m_Handle.InternalHandle = static_cast<void*>(PlatformWin32::InstanceHandler::GetWindow());
	RECT WindowRectangle;
	WindowRectangle.left = m_Config.x;
	WindowRectangle.top = m_Config.y;
	WindowRectangle.right = m_Config.width + WindowRectangle.left;
	WindowRectangle.bottom = m_Config.height + WindowRectangle.top;

	ICS_INFO("WIN32: Creating window class and retreiving handle...");
	if (!AdjustWindowRect(&WindowRectangle, WS_OVERLAPPEDWINDOW, FALSE)) { ICS_FATAL("WIN32: Cannot find window dimensions "); };
	m_Handle.InternalHandle = CreateWindow((LPCWSTR)InstanceHandler::GetWindowName(), (LPCWSTR)(wchar_t*)m_Config.name,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, WindowRectangle.right - WindowRectangle.left,
		WindowRectangle.bottom - WindowRectangle.top, nullptr, nullptr,
		InstanceHandler::GetInstance(), this);
	if (m_Handle.InternalHandle == nullptr) { ICS_FATAL("WIN32: Window handle is a nullptr, %p", m_Handle.InternalHandle) }
	else { ShowWindow(static_cast<HWND>(m_Handle.InternalHandle), SW_SHOWDEFAULT); ICS_DEBUG("WIN32: Window created at %p", m_Handle.InternalHandle); }
}

PlatformWin32::~PlatformWin32()
{
	if (m_Handle.InternalHandle)
	{
		DestroyWindow(static_cast<HWND>(m_Handle.InternalHandle)); ICS_INFO("WIN32: Window destroyed gracefully")
	}
}

bool PlatformWin32::ReadMessageQueue()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) { return false; }
		DispatchMessage(&msg);
		TranslateMessage(&msg);
	}
	// True to continue
	return true;
}

LRESULT CALLBACK PlatformWin32::DesignateObjectPointerToWindow(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) {
	if (msg == WM_NCCREATE) {
		PlatformWin32* const t_Window = static_cast<PlatformWin32*>(reinterpret_cast<CREATESTRUCTW*>(l_param)->lpCreateParams);
		SetWindowLongPtr(window, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(t_Window));
		SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&PlatformWin32::OnMessageReceived));
		return t_Window->OnMessageReceived(window, msg, w_param, l_param);
	}
	else { return DefWindowProc(window, msg, w_param, l_param); }
}

LRESULT CALLBACK PlatformWin32::OnMessageReceived(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) {

	//if (ImGui_ImplWin32_WndProcHandler(window, msg, w_param, l_param)) { return true; }

	switch (msg) {
	case WM_SIZE:
		if (w_param == SIZE_MINIMIZED) { break; }
	case WM_CLOSE:
	case WM_SIZING:
	case WM_KILLFOCUS:
		return reinterpret_cast<PlatformWin32*>(GetWindowLongPtr(window, GWLP_USERDATA))->OnStateMessage(window, msg, w_param, l_param);
	case WM_KEYUP:
	case WM_KEYDOWN:
	case WM_SYSKEYUP:
	case WM_SYSKEYDOWN:
		//if (ImGui::GetIO().WantCaptureKeyboard) { break; }
		return reinterpret_cast<PlatformWin32*>(GetWindowLongPtr(window, GWLP_USERDATA))->OnKeyMessage(window, msg, w_param, l_param);
	case WM_LBUTTONUP:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MOUSEMOVE:
	case WM_MOUSEWHEEL:
		//if (ImGui::GetIO().WantCaptureMouse) { break; }
		return reinterpret_cast<PlatformWin32*>(GetWindowLongPtr(window, GWLP_USERDATA))->OnMouseMessage(window, msg, w_param, l_param);
	}
	return DefWindowProc(window, msg, w_param, l_param);
}

LRESULT PlatformWin32::OnMouseMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) {
	m_EventHandler.GetMouseEvents().SetPositions(GET_X_LPARAM(l_param), GET_Y_LPARAM(l_param));
	switch (msg) {
	case WM_LBUTTONUP:
		m_EventHandler.GetMouseEvents().OnLeftButtonUp();
		break;
	case WM_LBUTTONDOWN:
		m_EventHandler.GetMouseEvents().OnLeftButtonDown();
		break;
	case WM_RBUTTONUP:
		m_EventHandler.GetMouseEvents().OnRightButtonUp();
		break;
	case WM_RBUTTONDOWN:
		m_EventHandler.GetMouseEvents().OnRightButtonDown();
		break;
	case WM_MBUTTONUP:
		m_EventHandler.GetMouseEvents().OnMiddleButtonUp();
		break;
	case WM_MBUTTONDOWN:
		m_EventHandler.GetMouseEvents().OnMiddleButtonDown();
		break;
	case WM_MOUSEMOVE:
		m_EventHandler.GetMouseEvents().OnMouseMoveEvent();
		break;
	case WM_MOUSEWHEEL:
		m_EventHandler.GetMouseEvents().OnScrollDeltaChange(GET_WHEEL_DELTA_WPARAM(w_param));
		break;
	}
	return DefWindowProc(window, msg, w_param, l_param);
}

LRESULT PlatformWin32::OnKeyMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) {
	switch (msg) {
	case WM_KEYUP:
	case WM_SYSKEYUP:
		m_EventHandler.GetKeyEvents().OnKeyUp((unsigned char)w_param);
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		m_EventHandler.GetKeyEvents().OnKeyDown((unsigned char)w_param);
		break;
	}

	return DefWindowProc(window, msg, w_param, l_param);
}

LRESULT PlatformWin32::OnStateMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KILLFOCUS:
		m_EventHandler.GetKeyEvents().FlushKeyQueue();
		break;
	case WM_SIZE:
	case WM_SIZING:
		RECT WindowRectangle = {};
		GetClientRect(window, &WindowRectangle);
		int width = WindowRectangle.right - WindowRectangle.left;
		int height = WindowRectangle.bottom - WindowRectangle.top;
		m_Config.width = width;
		m_Config.height = height;
		if (!AdjustWindowRect(&WindowRectangle, WS_OVERLAPPEDWINDOW, FALSE)) { ICS_FATAL("WIN32: Cannot resize window on WM_SIZE | WM_SIZING"); }
		m_EventHandler.GetStateEvents().AddStateEventToQueue(StateEvents::Event(StateEvents::Event::Type::WindowResize, width, height));
		break;
	}
	return DefWindowProc(window, msg, w_param, l_param);
}

#ifdef ICS_PLATFORM_WINDOWS

void Platform::PlatformErrorOut(const char* msg, unsigned int colour)
{
	// Windows specific console handle
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	// Logger::LogLevel mirror
	static unsigned int level[6] = { 64, 4, 6, 2, 1, 8 };
	SetConsoleTextAttribute(console, level[colour]);
	OutputDebugStringA(msg);
	unsigned int length = (unsigned int)strlen(msg);
	LPDWORD written = 0;
	WriteConsoleA(console, msg, (DWORD)length, written, 0);
	SetConsoleTextAttribute(console, (0 | 7)); // (0 | 7) is black background, white text
}

void Platform::PlatformConsoleOut(const char* msg, unsigned int colour)
{
	// Windows specific console handle
	HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
	// Logger::LogLevel mirror
	static unsigned int level[6] = { (BACKGROUND_RED), (BACKGROUND_RED | BACKGROUND_INTENSITY), (BACKGROUND_RED | BACKGROUND_BLUE), 13, 15, 8 };
	SetConsoleTextAttribute(console, level[colour]);
	OutputDebugStringA(msg);
	unsigned int length = (unsigned int)strlen(msg);
	LPDWORD written = 0;
	WriteConsoleA(console, msg, (DWORD)length, written, 0);
	SetConsoleTextAttribute(console, (0 | 7)); // (0 | 7) is black background, white text
}

#endif
