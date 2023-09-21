#pragma once

#include "Graphics/RenderFront/Scene/Mesh.h"

class Geometry : public Mesh
{
public:
	Geometry();
	virtual ~Geometry() = 0;

protected:
	bool FindNormals();
	bool FindTextureCoords();
	virtual bool FindIndices() = 0;
	virtual bool FindVertices() = 0;
};