#pragma once

#include "Graphics/DirectX11/Buffer/Buffer.h"
#include <Core/Structures/Buffers/Constants.h>

class ConstantBuffer : public Buffer {
public:
	ConstantBuffer() {}
	ConstantBuffer(Constants& cbuff);
	
	void BindBufferToPipeline() override;
};

