#pragma once

#include "Defines.h"

#include "Core/Structures/Scene/Root.h"

class Scene
{
public:
	Scene() {}

	inline darray<Root>& GetRoots() { return m_Roots; }
private:
	darray<Root> m_Roots;
};