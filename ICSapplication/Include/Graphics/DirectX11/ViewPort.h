#pragma once

#include <Defines.h>

class ViewPort {
	friend class RenderDirectX11;
public:
	ViewPort();
private:
	D3D11_VIEWPORT m_ViewPortDescription;
};
