#pragma once

#include "Containers/array/darray.h"
#include "Core/Application/Application.h"
#include "Graphics/RenderFront/Structure/Scene/Scene.h"

class UserInterface
{
public:
	virtual ~UserInterface() {}

	ICS_API virtual bool Startup() = 0;
	ICS_API virtual bool Update(float deltaTime) = 0;
	ICS_API virtual bool Render(float deltaTime) = 0;

	ICS_API inline void PushSceneToQueue(Scene& scene) { m_SceneQueue.PushToEnd(scene); }
	ICS_API inline Scene GetSceneFromQueue()
	{
		ICS_ASSERT_MSG(m_SceneQueue.Size() > 0, "UserInterface: Scene Queue must have at least one entry");
		Scene scene = m_SceneQueue[0u];
		m_SceneQueue.PopAt(0u);
		return scene;
	}
private: 
	darray<Scene> m_SceneQueue;
};

