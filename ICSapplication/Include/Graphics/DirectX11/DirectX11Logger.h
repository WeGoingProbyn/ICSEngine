#pragma once

#include <Defines.h>
#include <dxgidebug.h>

#include <Containers/array/darray.h>
#include <Containers/String/String.h>

class DirectX11Logger
{
public:
	DirectX11Logger();
	darray<String> GetInfoMessages();
	inline void SetCorrectIndexForMessages() { m_Index = m_LogQueue->GetNumStoredMessages(DXGI_DEBUG_ALL); }

private:
	unsigned long long m_Index = 0u;
	Microsoft::WRL::ComPtr<IDXGIInfoQueue> m_LogQueue;
};