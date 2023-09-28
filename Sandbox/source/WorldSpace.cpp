#include "WorldSpace.h"

#include <Utilities/FileIO/FileAsString.h>
#include <Core/Structures/Geometry/Square.h>
#include <Graphics/DirectX11/RenderDirectX11.h>

WorldSpace::WorldSpace()
{
}

WorldSpace::~WorldSpace()
{
}

void WorldSpace::OnRenderUpdate(RenderPlatform& platform)
{
	RenderDirectX11& dx11 = reinterpret_cast<RenderDirectX11&>(platform);

	for (Root& root : m_Scene.GetRoots())
	{
		dx11.BindVertices(root.GetMesh().GetInterleaved());
		dx11.BindVertexShader(root.GetMesh().GetShaders().GetBuffer()[0].GetShaderString());
		dx11.BindPixelShader(root.GetMesh().GetShaders().GetBuffer()[1].GetShaderString());

		// TODO: This currently assumes that there i only ever one node in the hierachy, this is obviously not good
		dx11.BindIndicesNodes(root.GetMesh().GetIndices().GetBuffer()[0]);
	}
}

