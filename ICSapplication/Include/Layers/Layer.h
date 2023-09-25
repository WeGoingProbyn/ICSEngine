#pragma once

#include "Defines.h"

#include "Graphics/RenderPlatform.h"

class Layer
{
public:
	Layer() {}

public:
	// TODO: Need to define vritual functions within render platform
	//		that describe the binding and drawing steps for each back end
	//		for now this is ok i guess...
	virtual void OnRenderUpdate(RenderPlatform& platform) {}
	
};