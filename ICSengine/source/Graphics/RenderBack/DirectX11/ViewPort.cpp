#include "Graphics/RenderBack/DirectX11/ViewPort.h"

ViewPort::ViewPort()
	:
	m_ViewPortDescription({}) {
	m_ViewPortDescription.MinDepth = 0;
	m_ViewPortDescription.MaxDepth = 1;
	m_ViewPortDescription.TopLeftX = 0;
	m_ViewPortDescription.TopLeftY = 0;
}