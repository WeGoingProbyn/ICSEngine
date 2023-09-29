#pragma once

#include "Core/Structures/Scene/Mesh.h"

class Geometry : public Mesh
{
public:
	Geometry();
	virtual ~Geometry() = 0;

protected:
	bool FindNormals();
	bool FindInterleaved();
	bool FindTextureCoords();
	virtual bool FindIndices() = 0;
	virtual bool FindVertices() = 0;

protected:
	darray<Vector<float, 3>> m_Normals;
	darray<Vector<float, 3>> m_Vertices;
	darray<Vector<float, 3>> m_TextureCoords;
	darray<darray<Vector<unsigned int, 3>>> m_Indices;
};