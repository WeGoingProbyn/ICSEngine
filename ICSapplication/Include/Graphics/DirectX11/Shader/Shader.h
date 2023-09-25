#pragma once

#include "Defines.h"

class Shader
{
public:
	virtual void CreateShader() = 0;
	virtual void BindShaderToPipeline() = 0;
protected:
	Shader();
	Shader(const char* path);
	virtual ~Shader() {}
protected:
	Microsoft::WRL::ComPtr<ID3DBlob> m_ByteBlob;
};


