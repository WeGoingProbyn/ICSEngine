#pragma once

#include "Layers/Layer.h"

#include <Core/Structures/Scene/Scene.h>

class WorldSpace : public Layer
{
public:
	ICS_API WorldSpace();
	ICS_API virtual ~WorldSpace();
	ICS_API void OnRenderUpdate(RenderPlatform& platform) override;

	inline void PushRootToScene(Mesh& mesh) { m_Scene.PushRootToScene(mesh); }
private:
	Scene m_Scene;
};