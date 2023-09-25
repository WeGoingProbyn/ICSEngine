#pragma once

#include "Graphics/DirectX11/Shader/Shader.h"

#include <Containers/String/String.h>

class PixelShader : public Shader {
public:
	PixelShader();
	PixelShader(String& src);
	void CreateShader() override;
	void BindShaderToPipeline() override;
	virtual ~PixelShader() {}
private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
};

