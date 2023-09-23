#include "Core/Structures/Scene/Node.h"

Node::Node()
	:
	m_Nodes(MemoryType::ICS_SCENE)
{
}

Node::Node(Indices::Node indices)
	:
	m_Nodes(MemoryType::ICS_SCENE)
{
}