#pragma once

#include <Defines.h>

#include <Core/Structures/Buffers/Shaders.h>
#include <Core/Structures/Buffers/Indices.h>
#include <Core/Structures/Buffers/Vertices.h>

class RenderPlatform
{
public:
	RenderPlatform() {}
	virtual ~RenderPlatform();

	virtual bool PresentDraw() = 0;
	virtual bool DrawBoundElements() = 0;

	virtual void BindShaders(Shaders& shaders) = 0;
	virtual void BindIndices(Indices& indices) = 0;
	virtual void BindVertices(Vertices& vertices) = 0;
};
