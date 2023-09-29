#include "Graphics/DirectX11/Buffer/VertexBuffer.h"

#include "Graphics/DirectX11/RenderDirectX11.h"

VertexBuffer::VertexBuffer()
	:
	Buffer() {}

VertexBuffer::VertexBuffer(Vertices& input)
	: 
	Buffer() {
	m_Offset = 0u;
	m_Stride = input.GetLayout().Size();
	//m_BaseSizeTotal = input.GetBuffer().GetNumberVertices();
	m_DataSize = input.GetBuffer().GetNumberVertices() * m_Stride;
	m_BufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	m_BufferDescription.Usage = D3D11_USAGE_IMMUTABLE;
	m_BufferDescription.CPUAccessFlags = 0u;
	m_BufferDescription.MiscFlags = 0u;
	m_BufferDescription.ByteWidth = m_DataSize * m_Stride;
	m_BufferDescription.StructureByteStride = m_Stride;  // lmao
	m_BufferInputHandle.pSysMem = input.GetBuffer().GetBufferPointer();
	CreateBuffer();
}

void VertexBuffer::BindBufferToPipeline() {
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->IASetVertexBuffers(0u, 1u, m_Buffer.GetAddressOf(), &m_Stride, &m_Offset);
}
