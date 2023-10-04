#pragma once

#include <Defines.h>
#include <Core/Structures/Scene/Scene.h>

#include "Graphics/Screen/ViewProjection.h"

#ifdef ICS_PLATFORM_WINDOWS
#include "Platform/PlatformWin32.h"
#include "Graphics/DirectX11/RenderDirectX11.h"
#endif

class RenderAPI
{
public:
	RenderAPI() {}
	ICS_API RenderAPI(unsigned int width, unsigned int height, void* window);

	ICS_API static void FinishDraw();
	ICS_API static void SetUpToDraw();
	ICS_API static void PresentDraw();
	ICS_API static void DrawScene(Scene& scene);
	ICS_API static void BindEntity(Entity& entity);

	ICS_API static Matrix<float, 4> Project(Transformation& transform);
	ICS_API static Matrix<float, 4> Project(Matrix<float, 4>& transform);

private:
	static ICS_API ViewProjection s_ViewProjection;

#ifdef ICS_PLATFORM_WINDOWS
	static RenderDirectX11 m_Render;
#endif
};