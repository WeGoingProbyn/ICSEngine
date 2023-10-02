#include "Core/Structures/Geometry/Circle.h"

#include <math.h>

Circle::Circle()
	:
	Circle(10u)
{ 
}

Circle::Circle(unsigned int faces)
	:
	m_Faces(faces)
{
	*this = Circle(faces, true);
}

Circle::Circle(unsigned int faces, bool build_buffers)
	:
	m_Faces(faces)
{
	*this = Circle(faces, 0.0f, false);
}

Circle::Circle(unsigned int faces, float base_origin_depth, bool build_buffers)
	:
	m_Faces(faces)
{
	FindVertices();
	for (Vector<float, 3>&vertex : m_Vertices)
	{
		vertex[2] += base_origin_depth;
	}
	FindIndices();

	if (build_buffers)
	{
		FindNormals();
		Indices::Hierachy hierachy(Indices::Type::TriangleList);
		hierachy.PushNodeToHierachy(m_Faces, 0u);
		m_Indexing = Indices(hierachy);
		FindInterleaved();
	}
}

Circle::~Circle()
{
}

bool Circle::FindIndices()
{	
	if (m_Indices.Size() == 0)
	{
		m_Indices.Resize(1u);
	}
	for (unsigned int index = 0; index < m_Faces; index++)
	{
		if (index < m_Faces - 1)
		{
			m_Indices[0].PushToEnd(Vector<unsigned int, 3>(0u, index + 1, index + 2));
		}
		else
		{
			m_Indices[0].PushToEnd(Vector<unsigned int, 3>(0u, index + 1, 1u));
		}
	}
	return true;
}

bool Circle::FindVertices()
{
	float radius = 1.0f;
	m_Vertices.PushToEnd({ 0.0f, 0.0f, 0.0f }); // Central point
	for (unsigned int index = 0; index < m_Faces; index++)
	{
		float ratio = (float)index / (float)m_Faces;
		float r = (float)ratio * (2.0f * 3.141592f);
		float x = std::cos(r) * radius;
		float y = std::sin(r) * radius;
		m_Vertices.PushToEnd({ x, y, 0.0f });
	}
	return true;
}
