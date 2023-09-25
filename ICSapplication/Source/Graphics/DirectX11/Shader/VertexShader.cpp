#include "Graphics/DirectX11/Shader/VertexShader.h"

#include <Core/Debugger/Logger.h>
#include "Graphics/DirectX11/RenderDirectX11.h"

VertexShader::VertexShader()
{
}

VertexShader::VertexShader(String& src)
{
	ICS_HRESULT_CHECK(D3DCompile(src.AsCstr(), src.GetSize(), nullptr, nullptr, nullptr, "main", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_ByteBlob, nullptr));


	// TODO: Need to pass the mesh vertices layout so this can be done dynamically, but for now this is fine...

	m_VertexElementDescription[0] = { "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	m_VertexElementDescription[1] = { "Normal", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	CreateShader();
}

void VertexShader::CreateShader() {
	ICS_HRESULT_CHECK(RenderDirectX11::StateAccess::GetInstance().m_Device->CreateVertexShader(m_ByteBlob->GetBufferPointer(),
																   m_ByteBlob->GetBufferSize(),
																   nullptr, &m_VertexShader));

	ICS_HRESULT_CHECK(RenderDirectX11::StateAccess::GetInstance().m_Device->CreateInputLayout(m_VertexElementDescription,
																  (UINT)std::size(m_VertexElementDescription),
																   m_ByteBlob->GetBufferPointer(), m_ByteBlob->GetBufferSize(),
																   &m_VertexLayout));
}

void VertexShader::BindShaderToPipeline() 
{
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->VSSetShader(m_VertexShader.Get(), 0, 0);
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->IASetInputLayout(m_VertexLayout.Get());
}
