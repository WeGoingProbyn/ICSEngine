#pragma once

#include <Layers/Layer.h>
#include <Core/Structures/Scene/Scene.h>
#include <Graphics/Screen/ViewProjection.h>

class WorldSpace : public Layer
{
public:
	WorldSpace();
	virtual ~WorldSpace();
	void OnRenderUpdate(Clock::Time& delta_time) override;

	inline ViewProjection& GetViewProjeciton() { return m_ViewProjection; }
	//inline void PushRoot(Mesh& mesh) { m_Scene.PushRoot(&mesh); }
private:
	Scene m_Scene;
	ViewProjection m_ViewProjection;
};