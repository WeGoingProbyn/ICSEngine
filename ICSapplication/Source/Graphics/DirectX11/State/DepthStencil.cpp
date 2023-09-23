#include "Graphics/DirectX11/State/DepthStencil.h"

DepthStencil::DepthStencil()
	:
	m_DepthStencilDesc({}),
	m_DepthStencilViewDesc({}),
	m_DepthStencilState(nullptr),
	m_DepthStencilTextureDesc({}) {
	
	m_DepthStencilDesc.DepthEnable = true;
	m_DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	m_DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // <- Fuck this mofo...

	m_DepthStencilTextureDesc.MipLevels = 1u;
	m_DepthStencilTextureDesc.ArraySize = 1u;
	m_DepthStencilTextureDesc.Format = DXGI_FORMAT_D32_FLOAT; // Only Depth testing
	m_DepthStencilTextureDesc.SampleDesc.Count = 1u;
	m_DepthStencilTextureDesc.SampleDesc.Quality = 0u;
	m_DepthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	m_DepthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	m_DepthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	m_DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	m_DepthStencilViewDesc.Texture2D.MipSlice = 0u;
}
