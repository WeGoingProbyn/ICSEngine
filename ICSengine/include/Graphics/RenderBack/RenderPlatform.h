#pragma once

#include "Defines.h"
#include "Graphics/RenderFront/Structure/Scene/Scene.h"

class RenderPlatform
{
public:
	RenderPlatform() {}
	virtual ~RenderPlatform() = 0;

	virtual bool DrawScene(Scene& scene) = 0;
};
