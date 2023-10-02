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

void Node::PropogateTransform(Transformation& accumulated)
{
	m_RelativeTransform = m_BaseTransform.Transform() * accumulated.Transform();
	if (m_Nodes.Size() > 0)
	{
		for (Node& node : m_Nodes)
		{
			node.PropogateTransform(m_RelativeTransform);
		}
	}
}

void Node::PropogateTransform(Matrix<float, 4> accumulated)
{
	m_RelativeTransform = m_BaseTransform.Transform() * accumulated;
	if (m_Nodes.Size() > 0)
	{
		for (Node& node : m_Nodes)
		{
			node.PropogateTransform(m_RelativeTransform);
		}
	}
}