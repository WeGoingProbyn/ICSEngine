#include "Core/Structures/Geometry/Arrow.h"

Arrow::Arrow()
	:
	m_Tip(Cone(10u, false)),
	m_Base(Cylinder(10u, false)),
	m_Hierachy(Indices::Type::TriangleList)
{
	Build(true);
}

Arrow::Arrow(unsigned int faces)
	:
	m_Tip(Cone(faces, false)),
	m_Base(Cylinder(faces, false)),
	m_Hierachy(Indices::Type::TriangleList)
{
	Build(true);
}

void Arrow::Build(bool build_buffers)
{
	FindVertices();
	FindIndices();
	FindNormals();

	if (build_buffers)
	{
		m_Indexing = Indices(m_Hierachy);
		FindInterleaved();
	}
}


Arrow::~Arrow()
{
}

bool Arrow::FindIndices()
{
	darray<Vector<unsigned int, 3>> tmp;
	for (Vector<unsigned int, 3>& indices : m_Base.m_Indices[0])
	{
		tmp.PushToEnd(indices);
	}
	m_Indices.PushToEnd(tmp);
	m_Hierachy.PushNodeToHierachy(m_Indices[m_Indices.Last()].Size(), 0u);
	tmp.Flush();
	darray<Vector<unsigned int, 3>> tmp2;
	for (Vector<unsigned int, 3>& indices : m_Tip.m_Indices[0])
	{
		tmp.PushToEnd(indices.Reverse());
	}
	m_Indices.PushToEnd(tmp);
	m_Hierachy.PushNodeToHierachy(m_Indices[m_Indices.Last()].Size(), 0u);
	return true;
}

bool Arrow::FindVertices()
{
	for (Vector<float, 3>&vertices : m_Base.m_Vertices)
	{
		m_Vertices.PushToEnd(vertices);
	}
	for (Vector<float, 3>&vertices : m_Tip.m_Vertices)
	{
		m_Vertices.PushToEnd(vertices);
	}
	return true;
}

bool Arrow::FindNormals()
{
	for (Vector<float, 3>&normal : m_Base.m_Normals)
	{
		m_Normals.PushToEnd(normal);
	}
	for (Vector<float, 3>&normal : m_Tip.m_Normals)
	{
		m_Normals.PushToEnd(normal.Reverse());
	}
	return true;
}