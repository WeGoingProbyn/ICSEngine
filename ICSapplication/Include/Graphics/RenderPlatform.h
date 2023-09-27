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

	virtual bool DrawClear() = 0;
	virtual bool DrawLayer() = 0;

	virtual void BindPixelShader(String& src) = 0;
	virtual void BindVertexShader(String& src) = 0;
	virtual void BindVertices(Vertices& vertices) = 0;
	virtual void BindIndicesNodes(Indices::Node indices) = 0;

	virtual void BindShaders(Shaders& shaders) = 0;
};
