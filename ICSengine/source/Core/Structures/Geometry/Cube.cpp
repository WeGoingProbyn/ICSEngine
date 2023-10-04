#include "Core/Structures/Geometry/Cube.h"

Cube::Cube()
{
	FindVertices();
	FindIndices();
	FindNormals();

	Indices::Hierachy hierachy(Indices::Type::TriangleList);
	hierachy.PushNodeToHierachy(12u, 0u);
	m_Indexing = Indices(hierachy);
	FindInterleaved();

	Transformation transform;
	transform.SetScale({ 1.0f, 1.0f, 1.0f });
	transform.SetRotation({ 0.0f, 0.0f, 0.0f });
	transform.SetTranslation({ 0.0f, 0.0f, 0.0f });
	m_BaseTransforms.PushToEnd(transform);
}

Cube::~Cube()
{
}

bool Cube::FindIndices()
{
	m_Indices.Resize(1u);
	m_Indices[0].PushToEnd({ 0u, 2u, 1u });
	m_Indices[0].PushToEnd({ 2u, 3u, 1u });
	m_Indices[0].PushToEnd({ 1u, 3u, 5u });
	m_Indices[0].PushToEnd({ 3u, 7u, 5u });
	m_Indices[0].PushToEnd({ 2u, 6u, 3u });
	m_Indices[0].PushToEnd({ 3u, 6u, 7u });
	m_Indices[0].PushToEnd({ 4u, 5u, 7u });
	m_Indices[0].PushToEnd({ 4u, 7u, 6u });
	m_Indices[0].PushToEnd({ 0u, 4u, 2u });
	m_Indices[0].PushToEnd({ 2u, 4u, 6u });
	m_Indices[0].PushToEnd({ 0u, 1u, 4u });
	m_Indices[0].PushToEnd({ 1u, 5u, 4u });
	return true;
}

bool Cube::FindVertices()
{
	m_Vertices.PushToEnd({ -0.5f, -0.5f, -0.5f });
	m_Vertices.PushToEnd({ 0.5f, -0.5f, -0.5f });
	m_Vertices.PushToEnd({ -0.5f, 0.5f, -0.5f });
	m_Vertices.PushToEnd({ 0.5f, 0.5f, -0.5f });
	m_Vertices.PushToEnd({ -0.5f, -0.5f, 0.5f });
	m_Vertices.PushToEnd({ 0.5f, -0.5f, 0.5f });
	m_Vertices.PushToEnd({ -0.5f, 0.5f, 0.5f });
	m_Vertices.PushToEnd({ 0.5f, 0.5f, 0.5f });
	return true;
}
