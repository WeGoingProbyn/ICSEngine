#include "WorldSpace.h"

#include <Managers/Assets.h>
#include <Graphics/RenderAPI.h>

#include <Utilities/FileIO/FileAsString.h>
#include <Core/Structures/Geometry/Cube.h>
#include <Core/Structures/Geometry/Square.h>

#include <Core/Structures/Spatial/Camera.h>
#include <Core/Structures/Spatial/Projection.h>
#include <Core/Structures/Spatial/Transformation.h>

WorldSpace::WorldSpace()
{
	Assets::PushToStack<Mesh>("Cube", Cube());
	Assets::PushToStack<Mesh>("Square", Square());
	Constants::Layout const_layout(Constants::Types::MATRIX);
	Shaders::Layout simple_layout(Shaders::Platform::DIRECTX, Shaders::Types::VERTEX, Shaders::Types::PIXEL);
	Assets::PushToStack<Shaders>("Simple", simple_layout, const_layout);
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/VertexShader.hlsl"));
	Assets::Get<Shaders>("Simple").PushSource(FileAsString::GetStringFromFile("Resource/Shader/PixelShader.hlsl"));	
	m_Scene.PushRoot(&Assets::Get<Mesh>("Cube"));
}

WorldSpace::~WorldSpace()
{
}

void WorldSpace::OnRenderUpdate()
{
	Camera camera;
	Transformation transform;
	transform.SetScale({ 10.0f, 10.0f, 10.0f });
	transform.SetRotation({ 0.0f, 0.0f, 0.0f });
	transform.SetTranslation({ 0.0f, 0.0f, 0.0f });
	Projection projection({ Platform::GetConfig().width, Platform::GetConfig().height });
	projection.PerspectiveProject();
	
	auto x = (transform.Transform() * camera.Translate() * projection.GetProjection()).Transpose();
	Matrix<float, 4> tmp;
	Assets::Get<Shaders>("Simple").FlushConstants();
	Assets::Get<Shaders>("Simple").PushConstant((transform.Transform() * camera.Translate() * projection.GetProjection()).Transpose());
	//Assets::Get<Shaders>("Simple").PushConstant(Matrix<float, 4>());
	
	RenderAPI::BindShaders(Assets::Get<Shaders>("Simple"));

	RenderAPI::SetUpToDraw();
	for (Root& root : m_Scene.GetRoots())
	{
		RenderAPI::BindMesh(root.GetMesh());
	}
	RenderAPI::PresentDraw();
}

