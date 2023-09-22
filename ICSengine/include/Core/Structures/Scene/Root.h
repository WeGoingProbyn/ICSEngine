#pragma once

#include "Core/Structures/Scene/Mesh.h"
#include "Core/Structures/Scene/Node.h"

class Root : public Node
{
public:
	Root() {}

	inline Mesh& GetMesh() { return m_Mesh; }
private:
	Mesh m_Mesh;
};