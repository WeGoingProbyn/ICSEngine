#pragma once

#include <Defines.h>
#include <Core/Structures/Scene/Mesh.h>

#ifdef ICS_PLATFORM_WINDOWS
#include "Platform/PlatformWin32.h"
#include "Graphics/DirectX11/RenderDirectX11.h"
#endif

class RenderAPI
{
public:
	RenderAPI() {}
	ICS_API RenderAPI(unsigned int width, unsigned int height, void* window);

	ICS_API static void SetUpToDraw();
	ICS_API static void PresentDraw();
	ICS_API static void BindMesh(Mesh& mesh);
	ICS_API static void BindShaders(Shaders& shaders);

private:
#ifdef ICS_PLATFORM_WINDOWS
	static RenderDirectX11 m_Render;
#endif
};