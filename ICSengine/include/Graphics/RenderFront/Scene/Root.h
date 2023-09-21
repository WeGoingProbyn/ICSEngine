#pragma once

#include "Graphics/RenderFront/Scene/Mesh.h"
#include "Graphics/RenderFront/Scene/Node.h"

class Root : public Node
{
public:
	Root() {}

	inline Mesh& GetMesh() { return m_Mesh; }
private:
	Mesh m_Mesh;
};