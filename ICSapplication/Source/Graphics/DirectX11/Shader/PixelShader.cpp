#include "Graphics/DirectX11/Shader/PixelShader.h"

#include "Core/Debugger/Logger.h"
#include "Graphics/DirectX11/RenderDirectX11.h"

PixelShader::PixelShader()
{
}

PixelShader::PixelShader(String& src)
{
	ICS_HRESULT_CHECK(D3DCompile(src.AsCstr(), src.GetSize(), nullptr, nullptr, nullptr, "main", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &m_ByteBlob, nullptr));
	//ICS_HRESULT_CHECK(D3DReadFileToBlob(L"../Binaries/Build/PixelShader.cso", &m_ByteBlob));

	CreateShader();
};

void PixelShader::CreateShader() {
	ICS_HRESULT_CHECK(RenderDirectX11::StateAccess::GetInstance().m_Device->CreatePixelShader(m_ByteBlob->GetBufferPointer(),
																							  m_ByteBlob->GetBufferSize(), 
																							  nullptr, &m_PixelShader));
}

void PixelShader::BindShaderToPipeline() { 
	RenderDirectX11::StateAccess::GetInstance().m_DeviceContext->PSSetShader(m_PixelShader.Get(), 0, 0);
}
