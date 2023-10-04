#include "WorldSpace.h"

#include <Managers/Assets.h>
#include <Graphics/RenderAPI.h>
#include <Application/Config.h>

#include <Utilities/FileIO/FileAsString.h>
#include <Core/Structures/Geometry/Cube.h>
#include <Core/Structures/Geometry/Cone.h>
#include <Core/Structures/Geometry/Arrow.h>
#include <Core/Structures/Geometry/Square.h>
#include <Core/Structures/Geometry/Cylinder.h>

#include <Core/Structures/Spatial/Camera.h>
#include <Core/Structures/Spatial/Projection.h>
#include <Core/Structures/Spatial/Transformation.h>

WorldSpace::WorldSpace()
{
	//Assets::PushToStack<Mesh>("Cube", Cube());
	//Assets::PushToStack<Mesh>("Square", Square());
	//Assets::PushToStack<Mesh>("Cone", Cone(3u));
	//Assets::PushToStack<Mesh>("Circle", Circle(5u));
	
	Assets::PushToStack<Mesh>("Arrow", Arrow(7u));
	Constants::Layout const_layout(Constants::Types::MATRIX);
	Shaders::Layout simple_layout(Shaders::Platform::DIRECTX, Shaders::Types::VERTEX, Shaders::Types::PIXEL);
	Assets::PushToStack<Shaders>("Simple", simple_layout, const_layout);
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/VertexShader.hlsl"));
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/PixelShader.hlsl"));	
	m_Scene.PushRoot(&Assets::Get<Mesh>("Arrow"));

	// TODO: There needs to be another layer between geometry and those derived with many geometries
	m_Scene.GetRoots()[0].GetBaseTransform().SetScale({ 0.05f, 0.05f, 1.5f });
	m_Scene.GetRoots()[0].GetBaseTransform().SetRotation({ 0.0f, 0.0f, 0.0f });
	m_Scene.GetRoots()[0].GetBaseTransform().SetTranslation({ 0.0f, 0.0f, 0.0f });

	m_Scene.GetRoots()[0].GetNodes()[0].GetBaseTransform().SetScale({ 1.5f, 1.5f, 0.5f });
	m_Scene.GetRoots()[0].GetNodes()[0].GetBaseTransform().SetRotation({ 180.0f, 0.0f, 0.0f });
	m_Scene.GetRoots()[0].GetNodes()[0].GetBaseTransform().SetTranslation({ 0.0f, 0.0f, 1.5f });

	//m_Scene.GetRoots()[1].GetBaseTransform().SetScale({ 1.0f, 1.0f, 1.0f });
	//m_Scene.GetRoots()[1].GetBaseTransform().SetRotation({ 0.0f, 0.0f, 0.0f });
	//m_Scene.GetRoots()[1].GetBaseTransform().SetTranslation({ 0.0f, 0.0f, 0.0f });
}

WorldSpace::~WorldSpace()
{
}

void WorldSpace::OnRenderUpdate(Clock::Time& delta_time)
{
	Transformation transform;
	transform.SetScale({ 1.0f, 1.0f, 1.0f });
	transform.SetRotation({ delta_time.Elapsed * 5.0f, delta_time.Elapsed * 20.0f, 0.0f});
	//transform.SetRotation({ 0.0f, 0.0f, 0.0f });
	transform.SetTranslation({ 0.0f, 0.0f, 4.0f });

	RenderAPI::SetUpToDraw();
	for (Root& root : m_Scene.GetRoots())
	{
		root.PropogateTransform(transform);
		Assets::Get<Shaders>("Simple").FlushConstants();
		Assets::Get<Shaders>("Simple").PushConstants(m_ViewProjection.Project(root.GetPropogatedTransform())); // TODO: Move view projection into Render API
		for (Node& node : root.GetNodes())
		{
			Assets::Get<Shaders>("Simple").PushConstants(m_ViewProjection.Project(node.GetPropogatedTransform())); // TODO: Move view projection into Render API
		}
		RenderAPI::BindMesh(root.GetMesh());
		RenderAPI::BindShaders(Assets::Get<Shaders>("Simple"));
		RenderAPI::PresentDraw();
	}
	RenderAPI::FinishDraw();
}

