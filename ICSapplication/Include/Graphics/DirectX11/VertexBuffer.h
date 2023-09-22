#pragma once

#include "Graphics/DirectX11/Buffer.h"

#include <Core/Structures/Buffers/Vertices.h>

class VertexBuffer : public Buffer {
public:
	VertexBuffer();
	VertexBuffer(Vertices& input);
	void BindBufferToPipeline() override;
	virtual ~VertexBuffer() {}
	inline UINT GetStride() { return m_Stride; }
	inline UINT GetOffset() { return m_Offset; }
private:
	UINT m_Stride;
	UINT m_Offset;
};
