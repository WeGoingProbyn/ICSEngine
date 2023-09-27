#include "Graphics/DirectX11/State/Rasterizer.h"

Rasterizer::Rasterizer()
	:
	m_ShouldUpdate(false)
{
	m_RasterDesc.AntialiasedLineEnable = false;
	m_RasterDesc.CullMode = D3D11_CULL_FRONT;
	m_RasterDesc.DepthBias = 0;
	m_RasterDesc.DepthBiasClamp = 0.0f;
	m_RasterDesc.DepthClipEnable = true;
	m_RasterDesc.SlopeScaledDepthBias = 0.0f;
	m_RasterDesc.FillMode = D3D11_FILL_SOLID;
	m_RasterDesc.FrontCounterClockwise = false;
	m_RasterDesc.MultisampleEnable = false;
	m_RasterDesc.ScissorEnable = false;
}