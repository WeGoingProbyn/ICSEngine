#pragma once

#include <Defines.h>

class RenderPlatform
{
public:
	RenderPlatform() {}
	virtual ~RenderPlatform() = 0;

	virtual bool DrawClear() = 0;
	virtual bool DrawLayer() = 0;
};
