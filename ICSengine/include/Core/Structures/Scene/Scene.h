#pragma once

#include "Defines.h"

#include "Core/Structures/Scene/Entity.h"

class Scene
{
public:
	ICS_API Scene();

	inline darray<Entity>& GetEntities() { return m_Entities; }
	inline void PushEntity(Mesh* mesh, Shaders* shaders) { m_Entities.PushToEnd({ mesh, shaders }); }
private:
	darray<Entity> m_Entities;
};