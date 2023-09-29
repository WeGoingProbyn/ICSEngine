#pragma once

#include <Layers/Layer.h>
#include <Core/Structures/Scene/Scene.h>

class WorldSpace : public Layer
{
public:
	WorldSpace();
	virtual ~WorldSpace();
	void OnRenderUpdate() override;

	//inline void PushRoot(Mesh& mesh) { m_Scene.PushRoot(&mesh); }
private:
	Scene m_Scene;
};