#pragma once

#include "Defines.h"
#include <Core/Debugger/Logger.h>

class Buffer {
public:
	void CreateBuffer();
	void UnBindBuffer();
	virtual void BindBufferToPipeline() = 0;
	virtual inline unsigned int GetDataSize() { return m_DataSize; }
	virtual inline unsigned int GetBaseSizeTotal() { return m_BaseSizeTotal; }
	virtual inline Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBuffer() { return m_Buffer; }
protected:
	Buffer();
	virtual ~Buffer() {}
protected:
	unsigned int m_DataSize;
	unsigned int m_BaseSizeTotal;
	D3D11_BUFFER_DESC m_BufferDescription;
	D3D11_SUBRESOURCE_DATA m_BufferInputHandle;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
};

