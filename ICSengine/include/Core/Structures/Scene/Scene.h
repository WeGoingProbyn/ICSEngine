#pragma once

#include "Defines.h"

#include "Core/Structures/Scene/Root.h"

class Scene
{
public:
	ICS_API Scene();

	inline darray<Root>& GetRoots() { return m_Roots; }
	inline void PushRootToScene(Mesh& mesh) { m_Roots.PushToEnd({ mesh }); }
private:
	darray<Root> m_Roots;
};