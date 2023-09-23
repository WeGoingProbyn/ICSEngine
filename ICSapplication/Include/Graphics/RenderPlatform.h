#pragma once

#include <Defines.h>
#include "Layers/Layer.h"

class RenderPlatform
{
public:
	RenderPlatform() {}
	virtual ~RenderPlatform() = 0;

	virtual bool DrawClear() = 0;
	virtual bool DrawLayer(Layer& layer) = 0;
};
