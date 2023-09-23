#include "Graphics/DirectX11/Buffer/IndexBuffer.h"

#include "Graphics/DirectX11/RenderDirectX11.h"

IndexBuffer::IndexBuffer()
	:
	Buffer() {}

IndexBuffer::IndexBuffer(Indices::Node& indices)
	:
	Buffer() 
{
	m_DataSize = indices.GetNodeHierachy()[indices.GetID()].GetSize();
	m_BufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	  // No changing
	m_BufferDescription.CPUAccessFlags = 0u;			  // No CPU access
	m_BufferDescription.MiscFlags = 0u;
	m_BufferDescription.ByteWidth = m_DataSize * indices.GetNodeHierachy()[indices.GetID()].GetElementStride();
	m_BufferDescription.StructureByteStride = sizeof(unsigned int); // Should always be using unsigned ints
	m_BufferInputHandle.pSysMem = indices.GetNodePointer();
	CreateBuffer();
}

void IndexBuffer::CleanUp() { }

IndexBuffer::~IndexBuffer() { }

void IndexBuffer::BindBufferToPipeline(){
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}