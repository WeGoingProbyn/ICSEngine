#include "Core/Structures/Geometry/Square.h"

Square::Square()
{
	FindVertices();
	FindIndices();
	FindNormals();

	Indices::Hierachy hierachy;
	hierachy.PushNodeToHierachy(2u, 0u, Indices::Type::TriangleList);

	m_Indexing = Indices(hierachy);
	m_Indexing.GetBuffer().PushNodeToBuffer(m_Indices[0]);

	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[0], m_Normals[0]);
	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[1], m_Normals[0]);
	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[2], m_Normals[0]);
	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[0], m_Normals[1]);
	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[2], m_Normals[1]);
	m_Interleaved.GetBuffer().PushVertexToBuffer(m_Vertices[3], m_Normals[1]);
}

Square::~Square()
{
}

bool Square::FindIndices()
{
	m_Indices.PushToEnd({ Vector<unsigned int, 3>(0u, 1u, 2u), Vector<unsigned int, 3>(3u, 4u, 5u) });
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
