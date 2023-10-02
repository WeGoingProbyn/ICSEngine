#include "Graphics/DirectX11/Buffer/ConstantBuffer.h"
#include "Graphics/DirectX11/RenderDirectX11.h"

ConstantBuffer::ConstantBuffer(Constants::Set cbuff) 
{
	m_BufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	m_BufferDescription.Usage = D3D11_USAGE_DYNAMIC;
	m_BufferDescription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_BufferDescription.MiscFlags = 0u;
	m_BufferDescription.ByteWidth = cbuff.GetLayout().Size();
	m_BufferDescription.StructureByteStride = 0u;
	m_BufferInputHandle.pSysMem = cbuff.GetRawPointer();
}

void ConstantBuffer::BindBufferToPipeline() 
{
	CreateBuffer();
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->VSSetConstantBuffers(0u, 1u, m_Buffer.GetAddressOf());
}