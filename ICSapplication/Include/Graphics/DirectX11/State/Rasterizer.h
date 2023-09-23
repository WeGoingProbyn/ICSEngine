#pragma once

#include <Defines.h>

class Rasterizer {
	friend class RenderDirectX11;
public:
	Rasterizer();
	inline void SetWireFrame(D3D11_FILL_MODE mode) { m_RasterDesc.FillMode = mode; }
	inline bool IsWireFrame() { if (m_RasterDesc.FillMode == D3D11_FILL_WIREFRAME) { return true; } else { return false; } }

private:
	bool m_ShouldUpdate;
	D3D11_RASTERIZER_DESC m_RasterDesc;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_Rasterizer;
};