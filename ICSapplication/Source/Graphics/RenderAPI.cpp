#include "Graphics/RenderAPI.h"

ViewProjection RenderAPI::s_ViewProjection;

#ifdef ICS_PLATFORM_WINDOWS
RenderDirectX11 RenderAPI::m_Render;
#endif

RenderAPI::RenderAPI(unsigned int width, unsigned int height, void* window)
{
	m_Render.StartUp(width, height, window);
	s_ViewProjection.OnStartUp();
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

void RenderAPI::BindEntity(Entity& entity)
{
	m_Render.BindVertices(entity.GetMesh().GetInterleaved());
	m_Render.BindIndices(entity.GetMesh().GetIndices());
	m_Render.BindShaders(entity.GetShaders());
}

void RenderAPI::DrawScene(Scene& scene)
{
	for (Entity& entity : scene.GetEntities())
	{
		BindEntity(entity);
		entity.FlushConstants();
		entity.PushConstants(Project(entity.GetRootPropogated()));
		for (Node& node : entity.GetRootNodes())
		{
			entity.PushConstants(node.GetPropogatedTransform());
		}
		m_Render.BindConstants(entity.GetConstants());
		m_Render.DrawBoundElements();
	}
	m_Render.FlipFrameBuffers();
}

ICS_API Matrix<float, 4> RenderAPI::Project(Matrix<float, 4>& transform)
{
	auto rtrn = s_ViewProjection.Project(transform, s_ViewProjection.GetCameraObj(), s_ViewProjection.GetProjectionObj());
	return rtrn;
}

ICS_API Matrix<float, 4> RenderAPI::Project(Transformation& transform)
{
	return s_ViewProjection.Project(transform, s_ViewProjection.GetCameraObj(), s_ViewProjection.GetProjectionObj());
}
