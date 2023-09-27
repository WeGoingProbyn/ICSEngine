#pragma once

#include <Layers/Layer.h>
#include <Core/Structures/Scene/Scene.h>

class WorldSpace : public Layer
{
public:
	WorldSpace();
	virtual ~WorldSpace();
	void OnRenderUpdate(RenderPlatform& platform) override;

	inline void PushRootToScene(Mesh& mesh) { m_Scene.PushRootToScene(mesh); }
private:
	Scene m_Scene;
};