#include "Core/Structures/Geometry/Cylinder.h"

Cylinder::Cylinder()
	:
	Circle(10u, false)
{
	Build(10u, true);
}

Cylinder::Cylinder(unsigned int faces)
	:
	Circle(faces, 1.0f, false)
{
	Build(faces, true);
}

Cylinder::Cylinder(unsigned int faces, bool build_buffers)
	:
	Circle(faces, 1.0f, false)
{
	Build(faces, build_buffers);
}

void Cylinder::Build(unsigned int faces, bool build_buffers)
{
	Circle::FindVertices();
	FindIndices();
	FindNormals();

	if (build_buffers)
	{
		Indices::Hierachy hierachy(Indices::Type::TriangleList);
		hierachy.PushNodeToHierachy(m_Indices[0].Size(), 0u);
		m_Indexing = Indices(hierachy);
		FindInterleaved();
	}
}

Cylinder::~Cylinder()
{
}

bool Cylinder::FindIndices()
{
	for (unsigned int index = 0; index < m_Faces; index++)
	{
		if (index < m_Faces - 1)
		{
			m_Indices[0].PushToEnd(Vector<unsigned int, 3>(m_Faces + 1, m_Faces + index + 2, m_Faces + index + 3).Reverse());
		}
		else
		{
			m_Indices[0].PushToEnd(Vector<unsigned int, 3>(m_Faces + 1, m_Faces + index + 2, m_Faces + 2).Reverse());
		}
	}

	for (unsigned int index = 0; index < m_Faces; index++)
	{
		m_Indices[0].PushToEnd(Vector<unsigned int, 3>(m_Indices[0][index][1], m_Indices[0][index][2], m_Indices[0][m_Faces + index][1]).Reverse());
	}

	for (unsigned int index = 0; index < m_Faces; index++)
	{
		m_Indices[0].PushToEnd(Vector<unsigned int, 3>(m_Indices[0][m_Faces + index][0], m_Indices[0][m_Faces + index][1], m_Indices[0][index][2]).Reverse());
	}
	return true;
}

bool Cylinder::FindVertices()
{
	Circle::FindVertices();
	return true;
}