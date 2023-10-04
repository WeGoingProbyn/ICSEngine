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
	Assets::PushToStack<Mesh>("Arrow", Cylinder(10u));
	Constants::Layout const_layout(Constants::Types::MATRIX);
	Shaders::Layout simple_layout(Shaders::Platform::DIRECTX, Shaders::Types::VERTEX, Shaders::Types::PIXEL);
	Assets::PushToStack<Shaders>("Simple", simple_layout, const_layout);
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/VertexShader.hlsl"));
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/PixelShader.hlsl"));

	m_Scene.PushEntity(&Assets::Get<Mesh>("Arrow"), &Assets::Get<Shaders>("Simple"));
}

WorldSpace::~WorldSpace()
{
}

void WorldSpace::OnRenderUpdate(Clock::Time& delta_time)
{
	Transformation transform;
	transform.SetScale({ 1.0f, 1.0f, 1.0f });
	transform.SetRotation({ delta_time.Elapsed * 5.0f, delta_time.Elapsed * 20.0f, 0.0f});
	//transform.SetRotation({ 0.0f, 90.0f, 0.0f});
	transform.SetTranslation({ 0.0f, 0.0f, 5.0f });

	RenderAPI::SetUpToDraw();
	for (Entity& ent : m_Scene.GetEntities())
	{
		ent.PropogateTransform(transform);
	}
	RenderAPI::DrawScene(m_Scene);
}

