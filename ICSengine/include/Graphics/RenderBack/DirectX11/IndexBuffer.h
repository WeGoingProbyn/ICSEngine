#pragma once

#include "Containers/Spatial/Vector.h"
#include "Graphics/RenderBack/DirectX11/Buffer.h"

class IndexBuffer : public Buffer 
{
public:
	IndexBuffer();
	IndexBuffer(Vector<unsigned int, 3>* input, unsigned int size);
	void BindBufferToPipeline() override;
	void CleanUp();
	~IndexBuffer();
};

