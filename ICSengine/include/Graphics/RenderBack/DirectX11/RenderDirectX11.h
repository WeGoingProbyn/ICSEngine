#pragma once

#include "Defines.h"

#include "Platform/Platform.h"
#include "Containers/Spatial/Vector.h"
#include "Graphics/RenderBack/RenderPlatform.h"
#include "Graphics/RenderBack/DirectX11/ViewPort.h"
#include "Graphics/RenderBack/DirectX11/Rasterizer.h"
#include "Graphics/RenderBack/DirectX11/DepthStencil.h"

#include "Graphics/RenderBack/DirectX11/IndexBuffer.h"
#include "Graphics/RenderBack/DirectX11/VertexBuffer.h"

class RenderDirectX11 : public RenderPlatform
{
public:
	RenderDirectX11() {}
	~RenderDirectX11();
	RenderDirectX11(int width, int height, HWND& window);
	bool DrawScene(Scene& scene) override;
private:
	bool CreateDepthStencil();
	bool CreateRasterizer();
	bool CreateTargetView();
	bool CreateViewPort();
	bool UnBindStates();

	bool BindBackBuffer();
	bool RebuildSwapChain();
	bool FlipFrameBuffers();
	bool BindBackBufferAndClearDepth();
	bool IndexDrawCall();
private:
	ViewPort m_ViewPort;
	Rasterizer m_Rasterizer;
	DepthStencil m_DepthStencil;
	Vector<int, 2> m_WindowSize;

	darray<IndexBuffer> m_IndexBuffers;
	darray<VertexBuffer> m_VertexBuffers;
public:
	class StateAccess
	{
	public:
		static StateAccess& GetInstance() { static StateAccess rtrn; return rtrn; }
	private:
		StateAccess() {}
		StateAccess(const StateAccess& rhs) = delete;
		const StateAccess& operator=(const StateAccess& rhs) = delete;
	public:
		DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;
		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11Resource> m_BackBuffer;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_TargetView;
	};
};