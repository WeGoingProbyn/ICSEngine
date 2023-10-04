#include "Graphics/RenderAPI.h"

#ifdef ICS_PLATFORM_WINDOWS
RenderDirectX11 RenderAPI::m_Render;
#endif

RenderAPI::RenderAPI(unsigned int width, unsigned int height, void* window)
{
	m_Render.StartUp(width, height, window);
}

void RenderAPI::BindMesh(Mesh& mesh)
{
	m_Render.BindVertices(mesh.GetInterleaved());
	m_Render.BindIndices(mesh.GetIndices());

}

void RenderAPI::BindShaders(Shaders& shaders)
{
	m_Render.BindShaders(shaders);
}

// TODO: Need to derive these functions from RenderPlatform
//		As right now these would all need to be functions inside render
void RenderAPI::SetUpToDraw()
{
	m_Render.BindBackBuffer();
}

void RenderAPI::PresentDraw()
{
	m_Render.DrawBoundElements();
}

void RenderAPI::FinishDraw()
{
	m_Render.FlipFrameBuffers();
}