#include "Graphics/RenderBack/DirectX11/IndexBuffer.h"
#include "Containers/Spatial/Vector.h"

#include "Graphics/RenderBack/DirectX11/RenderDirectX11.h"

IndexBuffer::IndexBuffer()
	:
	Buffer() {}

IndexBuffer::IndexBuffer(Vector<unsigned int, 3>* input, unsigned int size)
	:
	Buffer() {
	m_DataSize = size;
	m_BufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	m_BufferDescription.Usage = D3D11_USAGE_IMMUTABLE;	  // No changing
	m_BufferDescription.CPUAccessFlags = 0u;			  // No CPU access
	m_BufferDescription.MiscFlags = 0u;
	m_BufferDescription.ByteWidth = m_DataSize * sizeof(Vector<unsigned int, 3>);
	m_BufferDescription.StructureByteStride = sizeof(unsigned int);
	m_BufferInputHandle.pSysMem = input;
	CreateBuffer();
}

void IndexBuffer::CleanUp() { }

IndexBuffer::~IndexBuffer() { }

void IndexBuffer::BindBufferToPipeline(){
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
}