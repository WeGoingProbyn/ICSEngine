#pragma once

#include "Defines.h"
#include "Platform/Platform.h"
#include "Platform/EventOwner.h"

class PlatformWin32 : public Platform, public EventOwner
{
	friend class Application;
public:
	class InstanceHandler
	{
	private:
		InstanceHandler();
		~InstanceHandler();

		HWND m_Window;
		HINSTANCE m_Instance;
		static InstanceHandler m_InstanceHandle;
		static constexpr const char* m_WindowName = "In Computatrum Speramus";

	public:
		inline static HWND& GetWindow() { return m_InstanceHandle.m_Window; }
		inline static HINSTANCE& GetInstance() { return m_InstanceHandle.m_Instance; }
		inline static const char* GetWindowName() { return m_InstanceHandle.m_WindowName; }
	};
public:
	PlatformWin32();
	~PlatformWin32();
	bool ReadMessageQueue() override;

	LRESULT OnKeyMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param);
	LRESULT OnMouseMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param);
	LRESULT OnStateMessage(HWND window, UINT msg, WPARAM w_param, LPARAM l_param);
	static LRESULT CALLBACK OnMessageReceived(HWND window, UINT msg, WPARAM w_param, LPARAM l_param);
	static LRESULT CALLBACK DesignateObjectPointerToWindow(HWND window, UINT msg, WPARAM w_param, LPARAM l_param);
};