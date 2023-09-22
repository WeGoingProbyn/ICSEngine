#pragma once

#include "Containers/Spatial/Vector.h"
#include "Graphics/RenderBack/DirectX11/Buffer.h"
#include "Graphics/RenderFront/Buffers/Indices.h"

class IndexBuffer : public Buffer 
{
public:
	IndexBuffer();
	IndexBuffer(Indices::Node& indices);
	void BindBufferToPipeline() override;
	void CleanUp();
	~IndexBuffer();
};

