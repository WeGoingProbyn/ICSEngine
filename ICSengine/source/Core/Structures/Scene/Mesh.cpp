#include "Core/Structures/Scene/Mesh.h"

Mesh::Mesh()
	:
	m_Indices(MemoryType::ICS_MODEL),
	m_Normals(MemoryType::ICS_MODEL),
	m_Vertices(MemoryType::ICS_MODEL),
	m_TextureCoords(MemoryType::ICS_MODEL)
{
}