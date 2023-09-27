#include "Graphics/DirectX11/DirectX11Logger.h"

#include <memory>

#pragma comment(lib, "dxguid.lib")

DirectX11Logger::DirectX11Logger() {
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);
	const auto DxgiDebug = LoadLibraryEx(L"dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	ICS_ASSERT(DxgiDebug != nullptr);
	
	const auto DxgiDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(reinterpret_cast<void*>(
		GetProcAddress(DxgiDebug, "DXGIGetDebugInterface")));
	ICS_ASSERT(DxgiDebugInterface != nullptr);
	DxgiDebugInterface(__uuidof(IDXGIInfoQueue), &m_LogQueue);
	ICS_ASSERT(m_LogQueue != nullptr);
}

darray<String> DirectX11Logger::GetInfoMessages()
{
	darray<String> messages;
	const auto end = m_LogQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto index = m_Index; index < end; index++) {
		SIZE_T message_length = 0;

		ICS_HRESULT_CHECK(m_LogQueue->GetMessage(DXGI_DEBUG_ALL, index, nullptr, &message_length));
		auto bytes = std::make_unique<byte[]>(message_length);
		auto Message = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		ICS_HRESULT_CHECK(m_LogQueue->GetMessage(DXGI_DEBUG_ALL, index, Message, &message_length));
		messages.PushToEnd({ Message->pDescription });
	}
	return messages;
}