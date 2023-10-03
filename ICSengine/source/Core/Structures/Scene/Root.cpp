#include "Core/Structures/Scene/Root.h"

Root::Root()
	:
	m_Mesh(nullptr)
{
}

Root::Root(Mesh* mesh)
	:
	m_Mesh(mesh)
{
	for (unsigned int index = 0; index < m_Mesh->GetIndices().GetHierachy().GetTotalDescribedNodes(); index++)
	{
		m_Nodes.PushToEnd({ m_Mesh->GetIndices().GetBuffer()[index] });
		for (unsigned int node = 0; node < m_Mesh->GetIndices().GetHierachy()[index].GetNodeIDs().Size(); node++)
		{
			m_Nodes[m_Nodes.Last()].GetNodes().PushToEnd({ m_Mesh->GetIndices().GetBuffer()[node] });
		}
	}
}