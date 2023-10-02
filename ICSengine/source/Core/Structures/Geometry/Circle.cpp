#include "Core/Structures/Geometry/Circle.h"

#include <math.h>

Circle::Circle()
{
	FindVertices();
	FindIndices();
	FindNormals();

	Indices::Hierachy hierachy(Indices::Type::TriangleList);
	hierachy.PushNodeToHierachy(3u, 0u);
	m_Indexing = Indices(hierachy);

	FindInterleaved();
}


Circle::~Circle()
{
}

bool Circle::FindIndices()
{	
	unsigned int faces = 3u;
	Vector<unsigned int, 3> tmp(0u, 1u, 2u);
	m_Indices.PushToEnd({ tmp });
	for (unsigned int index = 1; index < faces; index++)
	{
		if (index < faces - 1)
		{
			m_Indices[0].PushToEnd({ 0u, index + 1, index + 2 });
		}
		else
		{
			m_Indices[0].PushToEnd({ 0u, index + 1, 1u });
		}
	}
	return true;
}

bool Circle::FindVertices()
{
	float radius = 1.0f;
	unsigned int faces = 3u;
	m_Vertices.PushToEnd({ 0.0f, 0.0f, 0.0f }); // Central point
	for (unsigned int index = 0; index < faces; index++)
	{
		float ratio = (float)index / (float)faces;
		float r = (float)ratio * (2.0f * 3.141592f);
		float x = std::cos(r) * radius;
		float y = std::sin(r) * radius;
		m_Vertices.PushToEnd({ x, y, 0.0f });
	}
	return true;
}
