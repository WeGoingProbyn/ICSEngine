#include "Graphics/DirectX11/Buffer.h"

#include "Graphics/DirectX11/RenderDirectX11.h"

Buffer::Buffer()
	:
	m_DataSize(0),
	m_BufferInputHandle({}),
	m_BufferDescription({}),
	m_Buffer(Microsoft::WRL::ComPtr<ID3D11Buffer>()) {}

void Buffer::CreateBuffer() 
{
	ICS_HRESULT_CHECK(RenderDirectX11::StateAccess::GetInstance().m_Device->CreateBuffer(&m_BufferDescription, &m_BufferInputHandle, &m_Buffer));
}

void Buffer::UnBindBuffer() { m_Buffer.Reset(); }

