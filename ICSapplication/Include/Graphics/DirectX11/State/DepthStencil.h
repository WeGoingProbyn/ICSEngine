#pragma once

#include "Defines.h"

class DepthStencil {
	friend class RenderDirectX11;
public:
	DepthStencil();
	inline Microsoft::WRL::ComPtr<ID3D11DepthStencilState> GetDepthStencilState() { return m_DepthStencilState; }
	inline Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return m_DepthStencilTargetView; }
private:
	D3D11_DEPTH_STENCIL_DESC m_DepthStencilDesc;
	D3D11_TEXTURE2D_DESC m_DepthStencilTextureDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC m_DepthStencilViewDesc;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilTargetView;
};