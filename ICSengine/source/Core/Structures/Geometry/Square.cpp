#include "Core/Structures/Geometry/Square.h"

Square::Square()
{
	FindVertices();
	FindIndices();
	FindNormals();

	Indices::Hierachy hierachy(Indices::Type::TriangleList);
	hierachy.PushNodeToHierachy(2u, 0u);
	m_Indexing = Indices(hierachy);
	
	FindInterleaved();
}

Square::~Square()
{
}

bool Square::FindIndices()
{
	m_Indices.PushToEnd({ Vector<unsigned int, 3>(0u, 1u, 2u), Vector<unsigned int, 3>(0u, 2u, 3u) });
	return true;
}

bool Square::FindVertices()
{
	m_Vertices.PushToEnd({ -0.5f, 0.5f, 0.0f });
	m_Vertices.PushToEnd({ -0.5f, -0.5f, 0.0f });
	m_Vertices.PushToEnd({ 0.5f, -0.5f, 0.0f });
	m_Vertices.PushToEnd({ 0.5f, 0.5f, 0.0f });
	return true;
}
