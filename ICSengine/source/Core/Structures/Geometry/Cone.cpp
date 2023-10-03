#include "Core/Structures/Geometry/Cone.h"

Cone::Cone()
	:
	Circle(10u, false)
{
	Build(true);
}

Cone::Cone(unsigned int faces)
	:
	Circle(faces, false)
{
	Build(true);
}

Cone::Cone(unsigned int faces, bool build_buffers)
	:
	Circle(faces, false)
{
	Build(build_buffers);
}

void Cone::Build(bool build_buffers)
{
	FindVertices();
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

Cone::~Cone()
{
}

bool Cone::FindIndices()
{
	for (Vector<unsigned int, 3>&face : m_Indices[0])
	{
		face = face.Reverse();
	}

	for (unsigned int index = 0; index < m_Faces; index++)
	{
		if (index < m_Faces - 1)
		{
			m_Indices[0].PushToEnd({ m_Vertices.Last(), index + 1, index + 2 });
		}
		else
		{
			m_Indices[0].PushToEnd({ m_Vertices.Last(), index + 1, 1u });
		}
	}
	return true;
}

bool Cone::FindVertices()
{
	m_Vertices.PushToEnd({ 0.0f, 0.0f, 1.0f });
	return true;
}