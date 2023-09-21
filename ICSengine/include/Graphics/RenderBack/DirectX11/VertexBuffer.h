#pragma once

#include "Graphics/RenderBack/DirectX11/Buffer.h"
#include "Graphics/RenderFront/Buffers/Vertices.h"

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
