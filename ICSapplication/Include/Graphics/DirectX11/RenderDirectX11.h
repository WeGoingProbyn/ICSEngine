#pragma once

#include <Defines.h>
#include <Containers/array/darray.h>
#include <Containers/Spatial/Vector.h>

#include "Platform/Platform.h"

#include "Graphics/RenderPlatform.h"
#include "Graphics/DirectX11/State/ViewPort.h"
#include "Graphics/DirectX11/State/Rasterizer.h"
#include "Graphics/DirectX11/State/DepthStencil.h"

#include "Graphics/DirectX11/Buffer/IndexBuffer.h"
#include "Graphics/DirectX11/Buffer/VertexBuffer.h"
#include "Graphics/DirectX11/Buffer/ConstantBuffer.h"

#include "Graphics/DirectX11/Shader/PixelShader.h"
#include "Graphics/DirectX11/Shader/VertexShader.h"

#include "Graphics/DirectX11/DirectX11Logger.h"

class RenderDirectX11 : public RenderPlatform
{
	friend class RenderAPI;
public:
	RenderDirectX11() {}
	~RenderDirectX11();
	RenderDirectX11(unsigned int width, unsigned int height, void* window);
	
	bool PresentDraw() override;
	bool DrawBoundElements() override;

	ICS_API void BindShaders(Shaders& shaders) override;
	ICS_API void BindIndices(Indices& indices) override;
	ICS_API void BindVertices(Vertices& vertices) override;


private:
	void StartUp(unsigned int width, unsigned int height, void* window);
	bool CreateDepthStencil();
	bool CreateRasterizer();
	bool CreateTargetView();
	bool CreateViewPort();
	bool UnBindStates();

	bool BindBackBuffer();
	bool RebuildSwapChain();
	bool FlipFrameBuffers();
	bool BindBackBufferAndClearDepth();

private:
	ViewPort m_ViewPort;
	Rasterizer m_Rasterizer;
	DepthStencil m_DepthStencil;
	Vector<int, 2> m_WindowSize;

	// TODO: This should maybe be contained within its own class...
	//		these might also benefit from being darray's..........
	VertexBuffer m_Vertices;
	PixelShader m_PixelShader;
	VertexShader m_VertexShader;
	darray<IndexBuffer> m_Indices;
	darray<ConstantBuffer> m_Constants;

	DirectX11Logger m_RenderLog;

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