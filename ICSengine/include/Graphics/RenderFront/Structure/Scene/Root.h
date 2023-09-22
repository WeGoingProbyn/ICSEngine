#pragma once

#include "Graphics/RenderFront/Structure/Scene/Mesh.h"
#include "Graphics/RenderFront/Structure/Scene/Node.h"

class Root : public Node
{
public:
	Root() {}

	inline Mesh& GetMesh() { return m_Mesh; }
private:
	Mesh m_Mesh;
};