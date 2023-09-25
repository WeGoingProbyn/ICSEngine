#include "Graphics/DirectX11/RenderDirectX11.h"


RenderDirectX11::RenderDirectX11(int width, int height, void* window)
{
	m_WindowSize(0) = width;
	m_WindowSize(1) = height;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.Width = 0;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.Height = 0;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	StateAccess::GetInstance().m_SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	StateAccess::GetInstance().m_SwapChainDesc.SampleDesc.Count = 1;
	StateAccess::GetInstance().m_SwapChainDesc.SampleDesc.Quality = 0;
	StateAccess::GetInstance().m_SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	StateAccess::GetInstance().m_SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	StateAccess::GetInstance().m_SwapChainDesc.BufferCount = 2u;
	StateAccess::GetInstance().m_SwapChainDesc.Windowed = TRUE;
	StateAccess::GetInstance().m_SwapChainDesc.OutputWindow = (HWND&)window;
	StateAccess::GetInstance().m_SwapChainDesc.Flags = 0;

	UINT CheckDebugCreateFlags = 0u;
#ifndef _DEBUG
	CheckDebugCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	ICS_HRESULT_CHECK(D3D11CreateDeviceAndSwapChain(nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		CheckDebugCreateFlags,
		nullptr, 0,
		D3D11_SDK_VERSION,
		&StateAccess::GetInstance().m_SwapChainDesc,
		&StateAccess::GetInstance().m_SwapChain, 
		&StateAccess::GetInstance().m_Device,
		nullptr, &StateAccess::GetInstance().m_DeviceContext));

	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_SwapChain->GetBuffer(0, _uuidof(ID3D11Resource), &StateAccess::GetInstance().m_BackBuffer));
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateRenderTargetView(StateAccess::GetInstance().m_BackBuffer.Get(), nullptr, &StateAccess::GetInstance().m_TargetView));

	CreateDepthStencil();
	CreateRasterizer();
	CreateViewPort();

	// TODO: This should be done dynamically
	StateAccess::GetInstance().m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

RenderDirectX11::~RenderDirectX11() {}

bool RenderDirectX11::BindBackBufferAndClearDepth() 
{
	StateAccess::GetInstance().m_DeviceContext->ClearDepthStencilView(m_DepthStencil.m_DepthStencilTargetView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	StateAccess::GetInstance().m_DeviceContext->OMSetRenderTargets(1u, StateAccess::GetInstance().m_TargetView.GetAddressOf(), m_DepthStencil.m_DepthStencilTargetView.Get());
	return true;
}

bool RenderDirectX11::FlipFrameBuffers()
{
	// Vsync, No Flags
	StateAccess::GetInstance().m_SwapChain->Present(1u, 0u);
	StateAccess::GetInstance().m_DeviceContext->ClearRenderTargetView(StateAccess::GetInstance().m_TargetView.Get(), Vector<float, 4>(0.0f, 0.0f, 0.0f, 0.0f).C_Arr());
	StateAccess::GetInstance().m_DeviceContext->ClearDepthStencilView(m_DepthStencil.m_DepthStencilTargetView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
	StateAccess::GetInstance().m_DeviceContext->OMSetRenderTargets(1u, StateAccess::GetInstance().m_TargetView.GetAddressOf(), m_DepthStencil.m_DepthStencilTargetView.Get());
	return true;
}

bool RenderDirectX11::CreateRasterizer() 
{
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateRasterizerState(&m_Rasterizer.m_RasterDesc, &m_Rasterizer.m_Rasterizer));
	StateAccess::GetInstance().m_DeviceContext->RSSetState(m_Rasterizer.m_Rasterizer.Get());
	return true;
}

bool RenderDirectX11::CreateDepthStencil() 
{
	m_DepthStencil.m_DepthStencilTextureDesc.Width = m_WindowSize(0);
	m_DepthStencil.m_DepthStencilTextureDesc.Height = m_WindowSize(1);
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateDepthStencilState(&m_DepthStencil.m_DepthStencilDesc, &m_DepthStencil.m_DepthStencilState));
	StateAccess::GetInstance().m_DeviceContext->OMSetDepthStencilState(m_DepthStencil.m_DepthStencilState.Get(), 1u);
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateTexture2D(&m_DepthStencil.m_DepthStencilTextureDesc, nullptr,
		&m_DepthStencil.m_DepthStencilTexture));
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateDepthStencilView(m_DepthStencil.m_DepthStencilTexture.Get(),
		&m_DepthStencil.m_DepthStencilViewDesc,
		&m_DepthStencil.m_DepthStencilTargetView));
	StateAccess::GetInstance().m_DeviceContext->OMSetRenderTargets(1u, StateAccess::GetInstance().m_TargetView.GetAddressOf(), m_DepthStencil.m_DepthStencilTargetView.Get());
	return true;
}

bool RenderDirectX11::CreateViewPort() 
{
	m_ViewPort.m_ViewPortDescription.Width = (float)m_WindowSize(0);
	m_ViewPort.m_ViewPortDescription.Height = (float)m_WindowSize(1);
	StateAccess::GetInstance().m_DeviceContext->RSSetViewports(1, &m_ViewPort.m_ViewPortDescription);
	return true;
}

bool RenderDirectX11::CreateTargetView() 
{
	Microsoft::WRL::ComPtr<IDXGIFactory> factory;
	ICS_HRESULT_CHECK(CreateDXGIFactory(IID_PPV_ARGS(factory.GetAddressOf())));
	ICS_HRESULT_CHECK(factory->CreateSwapChain(StateAccess::GetInstance().m_Device.Get(), &StateAccess::GetInstance().m_SwapChainDesc, &StateAccess::GetInstance().m_SwapChain));

	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_SwapChain->ResizeBuffers(0, (UINT)m_WindowSize(0), (UINT)m_WindowSize(1), DXGI_FORMAT_UNKNOWN, 0));
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &StateAccess::GetInstance().m_BackBuffer));
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateRenderTargetView(StateAccess::GetInstance().m_BackBuffer.Get(), nullptr, &StateAccess::GetInstance().m_TargetView));
	ICS_HRESULT_CHECK(StateAccess::GetInstance().m_Device->CreateRasterizerState(&m_Rasterizer.m_RasterDesc, &m_Rasterizer.m_Rasterizer));
	StateAccess::GetInstance().m_DeviceContext->RSSetState(m_Rasterizer.m_Rasterizer.Get());
	
	// TODO: This should be done dynamically using the given Indices object defined within engine
	StateAccess::GetInstance().m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}

bool RenderDirectX11::UnBindStates()
{
	StateAccess::GetInstance().m_SwapChain.Reset();
	StateAccess::GetInstance().m_BackBuffer.Reset();
	StateAccess::GetInstance().m_TargetView.Reset();
	StateAccess::GetInstance().m_DeviceContext->ClearState();
	StateAccess::GetInstance().m_DeviceContext->Flush();
	return true;
}

bool RenderDirectX11::RebuildSwapChain() 
{
	if (!UnBindStates()) { return false; }
	else if (!CreateTargetView()) { return false; }
	else if (!CreateDepthStencil()) { return false; }
	else if (!CreateViewPort()) { return false; }
	else { return true; }
}
bool RenderDirectX11::BindBackBuffer() 
{
	StateAccess::GetInstance().m_DeviceContext->OMSetRenderTargets(1u, StateAccess::GetInstance().m_TargetView.GetAddressOf(), m_DepthStencil.m_DepthStencilTargetView.Get());
	return true;
}

void RenderDirectX11::BindVertices(Vertices& vertices)
{
	m_Vertices = VertexBuffer(vertices);
	m_Vertices.BindBufferToPipeline();
}

void RenderDirectX11::BindIndicesNodes(Indices::Node indices)
{
	m_Indices = IndexBuffer(indices);
	m_Indices.BindBufferToPipeline();

	StateAccess::GetInstance().m_DeviceContext->DrawIndexed(6u, 0u, 0u);
}

void RenderDirectX11::BindPixelShader(String& src)
{
	m_PixelShader = PixelShader(src);
	m_PixelShader.BindShaderToPipeline();
}

void RenderDirectX11::BindVertexShader(String& src)
{
	m_VertexShader = VertexShader(src);
	m_VertexShader.BindShaderToPipeline();
}

bool RenderDirectX11::DrawClear()
{
	if (!FlipFrameBuffers()) { return false; }

	return true;
}

bool RenderDirectX11::DrawLayer()
{
	if (!FlipFrameBuffers()) { return false; }

	return true;
}
