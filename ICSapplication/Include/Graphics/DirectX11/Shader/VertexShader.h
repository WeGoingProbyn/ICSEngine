#pragma once

#include <Containers/String/String.h>

#include "Graphics/DirectX11/Shader/Shader.h"

class VertexShader : public Shader {
public:
	VertexShader();
	VertexShader(String& path);
	void CreateShader() override;
	void BindShaderToPipeline() override;
	virtual ~VertexShader() {}
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_VertexLayout;
	D3D11_INPUT_ELEMENT_DESC m_VertexElementDescription[2];
};

