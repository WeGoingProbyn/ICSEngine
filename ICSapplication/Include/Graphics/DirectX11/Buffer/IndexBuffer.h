#pragma once

#include <Containers/Spatial/Vector.h>
#include <Core/Structures/Buffers/Indices.h>

#include "Graphics/DirectX11/Buffer/Buffer.h"


class IndexBuffer : public Buffer 
{
public:
	IndexBuffer();
	~IndexBuffer();
	IndexBuffer(Indices::Node& indices);
	void BindBufferToPipeline() override;
	void CleanUp();
};

